#pragma once

class IAsmWrapper
{
public:
    IAsmWrapper() = default;
    virtual ~IAsmWrapper() = default;
    IAsmWrapper(const IAsmWrapper& other) = default;
    IAsmWrapper(IAsmWrapper&& other) noexcept = default;
    IAsmWrapper& operator=(const IAsmWrapper& other) = default;
    IAsmWrapper& operator=(IAsmWrapper&& other) noexcept = default;

    virtual void* GetPtr() = 0;
};
