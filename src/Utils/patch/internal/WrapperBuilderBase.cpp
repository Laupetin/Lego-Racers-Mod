#include "WrapperBuilderBase.h"

WrapperBuilderBase::WrapperBuilderBase(const UsercallConfiguration& usercallConfiguration)
    : m_usercall_configuration(usercallConfiguration)
{
}

bool WrapperBuilderBase::GetRegisterLocationForParam(const int paramIndex, Register* _register) const
{
    for (const auto& parameterLocation : m_usercall_configuration.m_parameter_locations)
    {
        if (parameterLocation.m_parameter_index == paramIndex)
        {
            *_register = parameterLocation.m_register;
            return true;
        }
    }

    return false;
}

void WrapperBuilderBase::ThrowIfError(const asmjit::Error error)
{
    const auto errorCode = static_cast<asmjit::ErrorCode>(error);

    if (errorCode != asmjit::ErrorCode::kErrorOk)
    {
        const char* errorMessage = asmjit::DebugUtils::errorAsString(error);
        printf("Could not assemble wrapper: %s\n", errorMessage);

        throw std::exception("Assemble wrapper failed");
    }
}
