#pragma once
#include <cstdint>
#include <memory>

#include "FunctionLike.h"

class Patch
{
public:
    static void Nop(uintptr_t ptr, size_t size);
    static void NopRange(uintptr_t start, uintptr_t end);
    static void Call(uintptr_t ptr, void* func);

    template<typename T>
    static void Call(const uintptr_t ptr, typename _Get_function_impl<T>::type::func_ptr_t func)
    {
        Call(ptr, reinterpret_cast<void*>(func));
    }

    static void Jump(uintptr_t ptr, void* func);

    template<typename T>
    static void Jump(const uintptr_t ptr, typename _Get_function_impl<T>::type::func_ptr_t func)
    {
        Jump(ptr, reinterpret_cast<void*>(func));
    }

    static void Data(uintptr_t ptr, const void* data, size_t dataSize);
    static void Data(void* ptr, const void* data, size_t dataSize);

    template <typename T>
    static void Field(void* ptr, T data)
    {
        Data(ptr, &data, sizeof(T));
    }

    template <typename T>
    static void Field(const uintptr_t ptr, T data)
    {
        Data(ptr, &data, sizeof(T));
    }

    template <typename T> static std::function<T> DoCall(uintptr_t function)
    {
        return std::function<T>(reinterpret_cast<T*>(function));
    }

    template <typename T> static std::function<T> DoCall(void* function)
    {
        return DoCall<T>(reinterpret_cast<DWORD>(function));
    }

    template<typename T>
    static __forceinline void* GetP(T a)
    {
        return *reinterpret_cast<void**>(&a);
    }
};
