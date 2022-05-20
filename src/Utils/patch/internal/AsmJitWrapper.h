#pragma once
#include "patch/IAsmWrapper.h"
#include "patch/Register.h"

#include <asmjit.h>
#include <mutex>
#include <memory>

#include "Singleton.h"

class AsmJitContext : public Singleton<AsmJitContext>
{
    asmjit::JitRuntime m_runtime;
    bool m_runtime_active;
    std::mutex m_runtime_lock;

public:
    AsmJitContext();
    ~AsmJitContext();
    static asmjit::x86::Gp GetRegister(Register parameterLocation);

    const asmjit::Environment& GetEnvironment() const;

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
