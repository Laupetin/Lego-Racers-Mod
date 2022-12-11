#pragma once
#include <memory>

#include "CallDetails.h"
#include "IAsmWrapper.h"
#include "UsercallConfiguration.h"

class StackToRegisterWrapperBuilder
{
public:
    static std::unique_ptr<IAsmWrapper> BuildWrapper(const void* offset,
                                                     const UsercallConfiguration& usercallConfiguration,
                                                     const size_t* paramSizes, int paramCount,
                                                     CallDetails from,
                                                     CallDetails to);
};
