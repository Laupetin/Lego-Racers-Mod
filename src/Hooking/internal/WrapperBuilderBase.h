#pragma once

#pragma warning(push, 0)
#include <asmjit.h>
#pragma warning(pop)

#include "Register.h"
#include "UsercallConfiguration.h"

class WrapperBuilderBase
{
protected:
    static constexpr size_t WORD_SIZE = sizeof(void*);

    const UsercallConfiguration& m_usercall_configuration;

    explicit WrapperBuilderBase(const UsercallConfiguration& usercallConfiguration);

    bool GetRegisterLocationForParam(const int paramIndex, Register* _register) const;
    static void ThrowIfError(asmjit::Error error);
};
