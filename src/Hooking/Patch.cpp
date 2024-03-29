#include "Patch.h"

#if defined(OS_TARGET_WINDOWS) && defined(ARCH_x86)

#include <Windows.h>
#include <cassert>

constexpr uint8_t OP_CALL_NEAR32 = 0xE8;
constexpr uint8_t OP_JMP_NEAR32 = 0xE9;
constexpr uint8_t OP_NOP = 0x90;

void Patch::Nop(const OffsetValue ptr, const size_t size)
{
    assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");

    Nop(ptr.m_fixed_value, size);
}

void Patch::Nop(const uintptr_t ptr, const size_t size)
{
    assert(ptr != 0);
    assert(size > 0);

    DWORD oldProtect;

    VirtualProtect(reinterpret_cast<void*>(ptr), size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(reinterpret_cast<void*>(ptr), OP_NOP, size);
    VirtualProtect(reinterpret_cast<void*>(ptr), size, oldProtect, &oldProtect);
}

void Patch::NopRange(const uintptr_t start, const uintptr_t end)
{
    assert(end >= start);
    Nop(start, end - start);
}

void Patch::NopRange(const OffsetValue start, const OffsetValue end)
{
    assert(start.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (start.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");

    assert(end.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (end.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");

    NopRange(start.m_fixed_value, end.m_fixed_value);
}

void Patch::Call(const uintptr_t ptr, void* func, const int size)
{
    const auto nopSize = static_cast<size_t>(std::max(size - 5, 0));

    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<void*>(ptr), sizeof uint8_t + sizeof uintptr_t + nopSize, PAGE_EXECUTE_READWRITE, &oldProtect);

    *reinterpret_cast<uint8_t*>(ptr) = OP_CALL_NEAR32;
    *reinterpret_cast<uintptr_t*>(ptr + 1) = reinterpret_cast<uintptr_t>(func) - ptr - 5;

    if (nopSize > 0)
        memset(reinterpret_cast<void*>(ptr + 5), OP_NOP, nopSize);

    VirtualProtect(reinterpret_cast<void*>(ptr), sizeof uint8_t + sizeof uintptr_t + nopSize, oldProtect, &oldProtect);
}

void Patch::Jump(const uintptr_t ptr, void* func)
{
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<void*>(ptr), sizeof uint8_t + sizeof uintptr_t, PAGE_EXECUTE_READWRITE, &oldProtect);

    *reinterpret_cast<uint8_t*>(ptr) = OP_JMP_NEAR32;
    *reinterpret_cast<uintptr_t*>(ptr + 1) = reinterpret_cast<uintptr_t>(func) - ptr - 5;

    VirtualProtect(reinterpret_cast<void*>(ptr), sizeof uint8_t + sizeof uintptr_t, oldProtect, &oldProtect);
}

void Patch::Data(const uintptr_t ptr, const void* data, const size_t dataSize)
{
    Data(reinterpret_cast<void*>(ptr), data, dataSize);
}

void Patch::Data(void* ptr, const void* data, const size_t dataSize)
{
    DWORD oldProtect;

    VirtualProtect(ptr, dataSize, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(ptr, data, dataSize);
    VirtualProtect(ptr, dataSize, oldProtect, &oldProtect);
}

void Patch::Data(const OffsetValue ptr, const void* data, const size_t dataSize)
{
    assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
    if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
        throw std::exception("Offset cannot be lazy");

    Data(ptr.m_fixed_value, data, dataSize);
}

#else

#include <iostream>

void Patch::Nop(const OffsetValue ptr, const size_t size)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Nop(const uintptr_t ptr, const size_t size)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::NopRange(const uintptr_t start, const uintptr_t end)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::NopRange(const OffsetValue start, const OffsetValue end)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Call(const uintptr_t ptr, void* func, const int size)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Jump(const uintptr_t ptr, void* func)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Data(const uintptr_t ptr, const void* data, const size_t dataSize)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Data(void* ptr, const void* data, const size_t dataSize)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

void Patch::Data(const OffsetValue ptr, const void* data, const size_t dataSize)
{
    std::cerr << "Hooking not supported on platform/architecture combination\n";
}

#endif
