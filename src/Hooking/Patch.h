#pragma once
#include "FunctionLike.h"
#include "OffsetBase.h"

#include <cstdint>
#include <memory>

class Patch
{
public:
    static void Nop(OffsetValue ptr, size_t size);
    static void Nop(uintptr_t ptr, size_t size);
    static void NopRange(OffsetValue start, OffsetValue end);
    static void NopRange(uintptr_t start, uintptr_t end);

    template<typename T> static void Call(const uintptr_t ptr, typename _Get_function_impl<T>::type::func_ptr_t func, const int size = -1)
    {
        Call(ptr, reinterpret_cast<void*>(func), size);
    }

    template<typename T> static void Call(const OffsetValue ptr, typename _Get_function_impl<T>::type::func_ptr_t func, const int size = -1)
    {
        assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
        if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
            throw std::exception("Offset cannot be lazy");

        Call(ptr.m_fixed_value, reinterpret_cast<void*>(func), size);
    }

    static void Call(OffsetValue ptr, void* func, int size = -1)
    {
        assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
        if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
            throw std::exception("Offset cannot be lazy");
        Call(ptr.m_fixed_value, func, size);
    }

    static void Call(uintptr_t ptr, void* func, int size = -1);

    template<typename T> static void Jump(const uintptr_t ptr, typename _Get_function_impl<T>::type::func_ptr_t func)
    {
        Jump(ptr, reinterpret_cast<void*>(func));
    }

    template<typename T> static void Jump(const OffsetValue ptr, typename _Get_function_impl<T>::type::func_ptr_t func)
    {
        assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
        if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
            throw std::exception("Offset cannot be lazy");

        Jump(ptr.m_fixed_value, reinterpret_cast<void*>(func));
    }

    static void Jump(uintptr_t ptr, void* func);

    static void Data(OffsetValue ptr, const void* data, size_t dataSize);
    static void Data(uintptr_t ptr, const void* data, size_t dataSize);
    static void Data(void* ptr, const void* data, size_t dataSize);

    template<typename T> static void Field(void* ptr, T data)
    {
        Data(ptr, &data, sizeof(T));
    }

    template<typename T> static void Field(const uintptr_t ptr, T data)
    {
        Data(ptr, &data, sizeof(T));
    }

    template<typename T> static void Field(const OffsetValue ptr, T data)
    {
        assert(ptr.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
        if (ptr.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
            throw std::exception("Offset cannot be lazy");

        Data(ptr.m_fixed_value, &data, sizeof(T));
    }

    template<typename T> static std::function<T> DoCall(uintptr_t function)
    {
        return std::function<T>(reinterpret_cast<T*>(function));
    }

    template<typename T> static std::function<T> DoCall(OffsetValue function)
    {
        assert(function.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION);
        if (function.m_lazy_evaluation_index != OffsetValue::NO_LAZY_EVALUATION)
            throw std::exception("Offset cannot be lazy");

        return std::function<T>(reinterpret_cast<T*>(function.m_fixed_value));
    }

    template<typename T> static std::function<T> DoCall(void* function)
    {
        return DoCall<T>(reinterpret_cast<uintptr_t>(function));
    }

    template<typename T> static __forceinline void* GetP(T a)
    {
        return *reinterpret_cast<void**>(&a);
    }
};
