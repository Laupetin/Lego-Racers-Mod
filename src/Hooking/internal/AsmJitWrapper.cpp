#include "AsmJitWrapper.h"

#include <memory>
#include <mutex>

AsmJitContext::AsmJitContext()
    : m_runtime_active(true)
{
}

AsmJitContext::~AsmJitContext()
{
    m_runtime_active = false;
}

asmjit::x86::Gp AsmJitContext::GetRegister(const Register parameterLocation)
{
    switch (parameterLocation)
    {
    case Register::EAX:
        return asmjit::x86::eax;
    case Register::EBX:
        return asmjit::x86::ebx;
    case Register::ECX:
        return asmjit::x86::ecx;
    case Register::EDX:
        return asmjit::x86::edx;
    case Register::ESI:
        return asmjit::x86::esi;
    case Register::EDI:
        return asmjit::x86::edi;
    case Register::INVALID:
    case Register::REGISTER_MAX:
    default:
        throw std::exception("Invalid register");
    }
}

const asmjit::Environment& AsmJitContext::GetEnvironment() const
{
    return m_runtime.environment();
}

void* AsmJitContext::AddWrapper(asmjit::CodeHolder* code)
{
    std::scoped_lock<std::mutex> lock(m_runtime_lock);

    void* result;
    const auto error = m_runtime.add(&result, code);

    if (error == asmjit::ErrorCode::kErrorOk)
        return result;

    return nullptr;
}

void AsmJitContext::RemoveWrapper(void* wrapper)
{
    std::scoped_lock<std::mutex> lock(m_runtime_lock);

    if (m_runtime_active)
        m_runtime.release(wrapper);
}

AsmJitWrapper::AsmJitWrapper(asmjit::CodeHolder* code)
{
    m_ptr = AsmJitContext::Instance().AddWrapper(code);
}

AsmJitWrapper::~AsmJitWrapper()
{
    if (m_ptr)
    {
        AsmJitContext::Instance().RemoveWrapper(m_ptr);
        m_ptr = nullptr;
    }
}

void* AsmJitWrapper::GetPtr()
{
    return m_ptr;
}
