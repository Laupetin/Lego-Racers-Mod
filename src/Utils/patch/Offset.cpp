#include "Offset.h"

TargetCompiler TrampolineGlobals::GetTargetCompiler() const
{
    return m_compiler;
}

void TrampolineGlobals::SetTargetCompiler(const TargetCompiler targetCompiler)
{
    m_compiler = targetCompiler;
}

FunctionOffsetUsercallBase::FunctionOffsetUsercallBase(std::function<void(UsercallConfiguration& usercall)> usercallInit)
    : m_wrapper(nullptr),
      m_usercall_configuration(nullptr),
      m_usercall_init(std::move(usercallInit))
{
}

void FunctionOffsetUsercallBase::InitWrapper(const uintptr_t offset, const size_t* paramSizes,
                                             const int paramCount, const size_t returnParamSize)
{
    if (m_usercall_init == nullptr)
        throw std::exception(
            "Usercall must have a valid init function. If there's no configuration to be made consider using a FunctionOffset instead.");

    m_usercall_configuration = std::make_unique<UsercallConfiguration>();
    m_usercall_init(*m_usercall_configuration);

    m_wrapper = StackToRegisterWrapperBuilder::BuildWrapper(reinterpret_cast<void*>(offset), *m_usercall_configuration, paramSizes,
                                                            paramCount, CallDetails(MY_COMPILER, MY_CALLING_CONVENTION),
                                                            CallDetails(CallingConvention::C_CDECL));
}

FunctionOffsetThiscallBase::FunctionOffsetThiscallBase()
    : m_wrapper(nullptr),
      m_usercall_configuration(nullptr)
{
}

void FunctionOffsetThiscallBase::InitWrapper(const uintptr_t offset, const size_t* paramSizes,
                                             const int paramCount, const size_t returnParamSize)
{
    m_usercall_configuration = std::make_unique<UsercallConfiguration>();
    m_usercall_configuration->FirstParameter().InEcx();

    m_wrapper = StackToRegisterWrapperBuilder::BuildWrapper(reinterpret_cast<void*>(offset), *m_usercall_configuration, paramSizes,
                                                            paramCount,
                                                            CallDetails(MY_COMPILER, MY_CALLING_CONVENTION),
                                                            CallDetails(CallingConvention::C_THISCALL));
}
