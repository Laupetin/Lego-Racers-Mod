#include "RegisterToStackWrapperBuilder.h"

#include <asmjit.h>

#include "internal/AsmJitWrapper.h"
#include "internal/WrapperBuilderBase.h"
#include "Offset.h"

class RegisterToStackWrapperBuilderInternal : public WrapperBuilderBase
{
    const void* m_offset;
    const size_t* m_param_sizes;
    const int m_param_count;
    int m_params_word_count;

public:
    RegisterToStackWrapperBuilderInternal(const void* offset, const UsercallConfiguration& usercallConfiguration,
                                          const size_t* paramSizes, const int paramCount)
        : WrapperBuilderBase(usercallConfiguration),
          m_offset(offset),
          m_param_sizes(paramSizes),
          m_param_count(paramCount),
          m_params_word_count(0)
    {
        for (int paramIndex = 0; paramIndex < paramCount; paramIndex++)
        {
            Register _register;
            if (!GetRegisterLocationForParam(paramIndex, &_register))
            {
                // Round up to next multiple of WORD_SIZE
                m_params_word_count += static_cast<int>((m_param_sizes[paramIndex] + WORD_SIZE - 1u) / WORD_SIZE);
            }
        }
    }

    std::unique_ptr<IAsmWrapper> BuildWrapper(const CallDetails from, const CallDetails to) const
    {
        Register nextRegister;
        asmjit::CodeHolder code;
        code.init(AsmJitContext::Instance().GetEnvironment());

        {
            using namespace asmjit::x86;

            Assembler assembler(&code);
            int pushedWordCount = 0;
            int paramWordOffset = m_params_word_count;

            for (int paramIndex = m_param_count - 1; paramIndex >= 0; paramIndex--)
            {
                const size_t paramSize = m_param_sizes[paramIndex];

                if (GetRegisterLocationForParam(paramIndex, &nextRegister))
                {
                    if (paramSize > WORD_SIZE)
                        throw std::exception(
                            "Cannot move parameter from register that is bigger than the system's word size.");

                    ThrowIfError(assembler.push(AsmJitContext::GetRegister(nextRegister)));
                    pushedWordCount++;
                    paramWordOffset++;
                }
                else
                {
                    // Round up to the next multiple of WORD_SIZE
                    const int paramWordCount = static_cast<int>((paramSize + WORD_SIZE - 1u) / WORD_SIZE);

                    for (int wordIndex = 0; wordIndex < paramWordCount; wordIndex++)
                    {
                        ThrowIfError(assembler.push(dword_ptr(esp, paramWordOffset * WORD_SIZE)));
                        pushedWordCount++;
                    }
                }
            }

            ThrowIfError(assembler.call(reinterpret_cast<uintptr_t>(m_offset)));
            
            if (!(to.m_compiler == TargetCompiler::MSVC && to.m_calling_convention == CallingConvention::C_THISCALL))
            {
                // Thiscall is callee cleanup on msvc
                ThrowIfError(assembler.add(esp, pushedWordCount * WORD_SIZE));
            }

            if (from.m_compiler == TargetCompiler::MSVC && from.m_calling_convention == CallingConvention::C_THISCALL)
            {
                // Thiscall is callee cleanup on msvc
                ThrowIfError(assembler.ret(m_params_word_count * WORD_SIZE));
            }
            else
            {
                ThrowIfError(assembler.ret());
            }
        }

        return std::make_unique<AsmJitWrapper>(&code);
    }
};

std::unique_ptr<IAsmWrapper> RegisterToStackWrapperBuilder::BuildWrapper(const void* offset,
                                                                         const UsercallConfiguration&
                                                                         usercallConfiguration,
                                                                         const size_t* paramSizes, const int paramCount,
                                                                         const CallDetails from,
                                                                         const CallDetails to)
{
    const RegisterToStackWrapperBuilderInternal builder(offset, usercallConfiguration, paramSizes, paramCount);
    return builder.BuildWrapper(from, to);
}
