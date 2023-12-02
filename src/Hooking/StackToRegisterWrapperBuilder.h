#pragma once
#include "CallDetails.h"
#include "IAsmWrapper.h"
#include "UsercallConfiguration.h"

#include <memory>

class StackToRegisterWrapperBuilder
{
public:
    static std::unique_ptr<IAsmWrapper> BuildWrapper(
        const void* offset, const UsercallConfiguration& usercallConfiguration, const size_t* paramSizes, int paramCount, CallDetails from, CallDetails to);
};
