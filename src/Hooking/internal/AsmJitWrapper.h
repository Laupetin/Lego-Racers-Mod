#pragma once
#include "IAsmWrapper.h"
#include "Register.h"

#include <memory>
#include <mutex>

#pragma warning(push, 0)
#include <asmjit.h>
#pragma warning(pop)

class AsmJitContext
{
    asmjit::JitRuntime m_runtime;
    bool m_runtime_active;
    std::mutex m_runtime_lock;

public:
    static AsmJitContext& Instance()
    {
        static AsmJitContext instance;
        return instance;
    }

    AsmJitContext();
    ~AsmJitContext();
    static asmjit::x86::Gp GetRegister(Register parameterLocation);

    [[nodiscard]] const asmjit::Environment& GetEnvironment() const;

    void* AddWrapper(asmjit::CodeHolder* code);
    void RemoveWrapper(void* wrapper);
};

class AsmJitWrapper final : public IAsmWrapper
{
    void* m_ptr;

public:
    explicit AsmJitWrapper(asmjit::CodeHolder* code);
    ~AsmJitWrapper() override;
    AsmJitWrapper(const AsmJitWrapper& other) = delete;
    AsmJitWrapper(AsmJitWrapper&& other) noexcept = default;
    AsmJitWrapper& operator=(const AsmJitWrapper& other) = delete;
    AsmJitWrapper& operator=(AsmJitWrapper&& other) noexcept = default;

    void* GetPtr() override;
};
