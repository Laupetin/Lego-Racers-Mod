#pragma once
#include "CallDetails.h"
#include "IAsmWrapper.h"
#include "UsercallConfiguration.h"

#include <memory>

class RegisterToStackWrapperBuilder
{
public:
    static std::unique_ptr<IAsmWrapper> BuildWrapper(
        const void* offset, const UsercallConfiguration& usercallConfiguration, const size_t* paramSizes, int paramCount, CallDetails from, CallDetails to);
};
