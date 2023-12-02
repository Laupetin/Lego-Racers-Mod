#include "Detour.h"

#include "Patch.h"

#include <limits>

#pragma warning(push, 0)
#include <Zydis/Zydis.h>
#include <asmjit.h>
#pragma warning(pop)

#include "Internal/AsmJitWrapper.h"
#include "RegisterToStackWrapperBuilder.h"
#include "StackToRegisterWrapperBuilder.h"

class TrampolineBuilder
{
    uintptr_t m_start_address;
    size_t m_minimum_length;
    size_t m_current_offset;
    ZydisDecoder m_decoder;
    asmjit::CodeHolder m_code;

public:
    TrampolineBuilder(uintptr_t dataAddress, size_t trampolineMinimumLength)
        : m_start_address(dataAddress),
          m_minimum_length(trampolineMinimumLength),
          m_current_offset(0),
          m_decoder()
    {
        m_code.init(AsmJitContext::Instance().GetEnvironment());
        ZydisDecoderInit(&m_decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_STACK_WIDTH_32);
    }

    void GenerateAssemblyCode()
    {
        using namespace asmjit::x86;

        ZydisDecodedInstruction instr;
        ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
        Assembler assembler(&m_code);
        bool omitJumpBack = false;
        while (m_current_offset < m_minimum_length
               && ZYAN_SUCCESS(ZydisDecoderDecodeFull(&m_decoder,
                                                      reinterpret_cast<void*>(m_start_address + m_current_offset),
                                                      std::numeric_limits<ZyanUSize>::max(),
                                                      &instr,
                                                      operands,
                                                      static_cast<ZyanU8>(std::extent_v<decltype(operands)>),
                                                      0)))
        {
            switch (instr.mnemonic)
            {
            case ZYDIS_MNEMONIC_JMP:
                omitJumpBack = true;
                assembler.jmp(static_cast<uint64_t>(m_start_address) + m_current_offset + instr.length + operands[0].imm.value.s);
                break;
            case ZYDIS_MNEMONIC_CALL:
                assembler.call(static_cast<uint64_t>(m_start_address) + m_current_offset + instr.length + operands[0].imm.value.s);
                break;
            case ZYDIS_MNEMONIC_JO:
            case ZYDIS_MNEMONIC_JNO:
            case ZYDIS_MNEMONIC_JS:
            case ZYDIS_MNEMONIC_JNS:
            case ZYDIS_MNEMONIC_JZ:
            case ZYDIS_MNEMONIC_JNZ:
            case ZYDIS_MNEMONIC_JB:
            case ZYDIS_MNEMONIC_JNB:
            case ZYDIS_MNEMONIC_JBE:
            case ZYDIS_MNEMONIC_JNBE:
            case ZYDIS_MNEMONIC_JL:
            case ZYDIS_MNEMONIC_JNL:
            case ZYDIS_MNEMONIC_JLE:
            case ZYDIS_MNEMONIC_JNLE:
            case ZYDIS_MNEMONIC_JP:
            case ZYDIS_MNEMONIC_JNP:
            case ZYDIS_MNEMONIC_JECXZ:
                throw std::exception("Creating a trampoline containing conditional jumps is unsupported");
            default:
                assembler.embed(reinterpret_cast<void*>(m_start_address + m_current_offset), instr.length);
                break;
            }

            m_current_offset += instr.length;
        }

        if (!omitJumpBack)
            assembler.jmp(static_cast<uint64_t>(m_start_address) + m_current_offset);
    }

    std::unique_ptr<IAsmWrapper> BuildTrampoline()
    {
        GenerateAssemblyCode();

        return std::make_unique<AsmJitWrapper>(&m_code);
    }
};

DetourBase::DetourBase()
    : m_installed(false),
      m_original_data(nullptr),
      m_original_data_size(0),
      m_address(0),
      m_detour_func_ptr(nullptr)
{
}

DetourBase::DetourBase(const uintptr_t address)
    : m_installed(false),
      m_original_data(nullptr),
      m_original_data_size(0),
      m_address(address),
      m_detour_func_ptr(nullptr)
{
}

DetourBase::DetourBase(const OffsetValue address)
    : m_installed(false),
      m_original_data(nullptr),
      m_original_data_size(0),
      m_detour_func_ptr(nullptr)
{
    assert(address.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (address.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");
    m_address = address.m_fixed_value;
}

DetourBase::DetourBase(const uintptr_t address, void* detourFuncPtr)
    : m_installed(false),
      m_original_data(nullptr),
      m_original_data_size(0),
      m_address(address),
      m_detour_func_ptr(detourFuncPtr)
{
}

DetourBase::DetourBase(const OffsetValue address, void* detourFuncPtr)
    : m_installed(false),
      m_original_data(nullptr),
      m_original_data_size(0),
      m_detour_func_ptr(detourFuncPtr)
{
    assert(address.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (address.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");
    m_address = address.m_fixed_value;
}

DetourBase::DetourBase(DetourBase&& other) noexcept
    : m_installed(other.m_installed),
      m_original_data(std::move(other.m_original_data)),
      m_original_data_size(other.m_original_data_size),
      m_address(other.m_address),
      m_detour_func_ptr(other.m_detour_func_ptr)
{
    other.m_installed = false;
}

DetourBase& DetourBase::operator=(DetourBase&& other) noexcept
{
    if (this == &other)
        return *this;

    m_installed = other.m_installed;
    m_original_data = std::move(other.m_original_data);
    m_original_data_size = other.m_original_data_size;
    m_address = other.m_address;
    m_detour_func_ptr = other.m_detour_func_ptr;

    other.m_installed = false;

    return *this;
}

void DetourBase::Install(const DetourType type)
{
    m_original_data_size = 5;
    m_original_data = std::make_unique<uint8_t[]>(m_original_data_size);
    memcpy(m_original_data.get(), reinterpret_cast<void*>(m_address), m_original_data_size);

    switch (type)
    {
    case DetourType::JUMP:
        Patch::Jump(m_address, m_detour_func_ptr);
        break;
    case DetourType::CALL:
        Patch::Call(m_address, m_detour_func_ptr);
        break;
    default:
        throw std::exception("Unknown detour type");
    }

    m_installed = true;
}

DetourBase::~DetourBase()
{
    if (m_installed)
    {
        Patch::Data(m_address, m_original_data.get(), m_original_data_size);
        m_installed = false;
    }
}

DetourTrampolineBase::DetourTrampolineBase() = default;

DetourTrampolineBase::DetourTrampolineBase(const uintptr_t address, void* detourFuncPtr)
    : DetourBase(address, detourFuncPtr),
      m_trampoline(nullptr)
{
}

void DetourTrampolineBase::BuildTrampoline()
{
    TrampolineBuilder builder(m_address, 5);
    m_trampoline = builder.BuildTrampoline();
}

DetourTrampolineBase::~DetourTrampolineBase() = default;

DetourUsercallBase::DetourUsercallBase() = default;

DetourUsercallBase::DetourUsercallBase(const uintptr_t address)
    : DetourBase(address)
{
}

DetourUsercallBase::DetourUsercallBase(const OffsetValue address)
{
    assert(address.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (address.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");
    m_address = address.m_fixed_value;
}

void DetourUsercallBase::InitWrapper(const void* userFunc,
                                     const size_t* paramSizes,
                                     const int paramCount,
                                     size_t returnParamSize,
                                     const UsercallConfiguration& usercallConfiguration,
                                     const CallingConvention callingConvention)
{
    m_wrapper = RegisterToStackWrapperBuilder::BuildWrapper(
        userFunc, usercallConfiguration, paramSizes, paramCount, CallDetails(callingConvention), CallDetails(MY_COMPILER, MY_CALLING_CONVENTION));
    m_detour_func_ptr = m_wrapper->GetPtr();
}

DetourUsercallBase::~DetourUsercallBase() = default;

DetourTrampolineUsercallBase::DetourTrampolineUsercallBase() = default;

DetourTrampolineUsercallBase::DetourTrampolineUsercallBase(const uintptr_t address)
    : DetourUsercallBase(address)
{
}

void DetourTrampolineUsercallBase::BuildTrampoline(const size_t* paramSizes,
                                                   const int paramCount,
                                                   size_t returnParamSize,
                                                   const UsercallConfiguration& usercallConfiguration,
                                                   const CallingConvention callingConvention)
{
    TrampolineBuilder builder(m_address, 5);
    m_trampoline = builder.BuildTrampoline();

    m_trampoline_wrapper = StackToRegisterWrapperBuilder::BuildWrapper(
        m_trampoline->GetPtr(), usercallConfiguration, paramSizes, paramCount, CallDetails(MY_COMPILER, MY_CALLING_CONVENTION), CallDetails(callingConvention));
}

DetourTrampolineUsercallBase::~DetourTrampolineUsercallBase() = default;
