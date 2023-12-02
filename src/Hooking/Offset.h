#pragma once

#include "CallDetails.h"
#include "FunctionLike.h"
#include "OffsetBase.h"
#include "StackToRegisterWrapperBuilder.h"
#include "UsercallConfiguration.h"

#include <cstdint>
#include <functional>

class BaseOffset;

class TrampolineGlobals
{
    TargetCompiler m_compiler = TargetCompiler::UNKNOWN;

public:
    static TrampolineGlobals& Instance()
    {
        static TrampolineGlobals instance;
        return instance;
    }

    [[nodiscard]] TargetCompiler GetTargetCompiler() const;
    void SetTargetCompiler(TargetCompiler targetCompiler);
};

template<class T> class FunctionOffset final : public _Get_function_impl<T>::type, ILazyOffsetInitTarget
{
public:
    using _Get_function_impl<T>::type::m_func;

    explicit FunctionOffset(const OffsetValue value)
        : _Get_function_impl<T>::type()
    {
        if (value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
            m_func = reinterpret_cast<void*>(value.m_fixed_value);
        else
            OffsetManager::RegisterLazyInitialization(this, value.m_lazy_evaluation_index);
    }

    explicit FunctionOffset(void* value)
        : _Get_function_impl<T>::type()
    {
        m_func = value;
    }

    explicit FunctionOffset(const uintptr_t value)
        : _Get_function_impl<T>::type()
    {
        m_func = reinterpret_cast<void*>(value);
    }

    void SetLazyValue(const uintptr_t value) override
    {
        m_func = reinterpret_cast<void*>(value);
    }
};

template<class T> class FunctionOffsetStdcall final : public _Get_function_impl_stdcall<T>::type, ILazyOffsetInitTarget
{
public:
    using _Get_function_impl_stdcall<T>::type::m_func;

    explicit FunctionOffsetStdcall(const OffsetValue value)
        : _Get_function_impl_stdcall<T>::type()
    {
        if (value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
            m_func = reinterpret_cast<void*>(value.m_fixed_value);
        else
            OffsetManager::RegisterLazyInitialization(this, value.m_lazy_evaluation_index);
    }

    explicit FunctionOffsetStdcall(void* value)
        : _Get_function_impl_stdcall<T>::type()
    {
        m_func = value;
    }

    explicit FunctionOffsetStdcall(const uintptr_t value)
        : _Get_function_impl_stdcall<T>::type()
    {
        m_func = reinterpret_cast<void*>(value);
    }

    void SetLazyValue(const uintptr_t value) override
    {
        m_func = reinterpret_cast<void*>(value);
    }
};

template<class T> class FunctionOffsetVarArgs final : public _Get_function_impl_varargs<T>::type, ILazyOffsetInitTarget
{
public:
    using _Get_function_impl_varargs<T>::type::m_func;

    explicit FunctionOffsetVarArgs(const OffsetValue value)
        : _Get_function_impl_varargs<T>::type()
    {
        if (value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
            m_func = reinterpret_cast<void*>(value.m_fixed_value);
        else
            OffsetManager::RegisterLazyInitialization(this, value.m_lazy_evaluation_index);
    }

    explicit FunctionOffsetVarArgs(void* value)
        : _Get_function_impl_varargs<T>::type()
    {
        m_func = value;
    }

    explicit FunctionOffsetVarArgs(const uintptr_t value)
        : _Get_function_impl_varargs<T>::type()
    {
        m_func = reinterpret_cast<void*>(value);
    }

    void SetLazyValue(const uintptr_t value) override
    {
        m_func = reinterpret_cast<void*>(value);
    }
};

class FunctionOffsetUsercallBase
{
protected:
    std::unique_ptr<IAsmWrapper> m_wrapper;
    std::unique_ptr<UsercallConfiguration> m_usercall_configuration;
    std::function<void(UsercallConfiguration& usercall)> m_usercall_init;

    FunctionOffsetUsercallBase(std::function<void(UsercallConfiguration& usercall)> usercallInit);
    void InitWrapper(uintptr_t offset, const size_t* paramSizes, int paramCount, size_t returnParamSize);
};

template<class T>
class FunctionOffsetUsercall final : public _Get_function_impl<T>::type,
                                     public _Get_function_impl_param_capture<T>::type,
                                     public FunctionOffsetUsercallBase,
                                     ILazyOffsetInitTarget
{
public:
    using FunctionOffsetUsercallBase::m_wrapper;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_return_size;
    using _Get_function_impl<T>::type::m_func;

    FunctionOffsetUsercall(const OffsetValue value, const std::function<void(UsercallConfiguration& usercall)> usercallInit)
        : _Func_class_param_capture(),
          FunctionOffsetUsercallBase(usercallInit)
    {
        if (value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
        {
            InitWrapper(value.m_fixed_value, m_param_sizes, m_param_count, m_return_size);

            if (m_wrapper != nullptr)
                m_func = m_wrapper->GetPtr();
            else
                m_func = nullptr;
        }
        else
            OffsetManager::RegisterLazyInitialization(this, value.m_lazy_evaluation_index);
    }

    void SetLazyValue(const uintptr_t value) override
    {
        InitWrapper(value, m_param_sizes, m_param_count, m_return_size);

        if (m_wrapper != nullptr)
            m_func = m_wrapper->GetPtr();
        else
            m_func = nullptr;
    }
};

class FunctionOffsetThiscallBase
{
protected:
    std::unique_ptr<IAsmWrapper> m_wrapper;
    std::unique_ptr<UsercallConfiguration> m_usercall_configuration;

    FunctionOffsetThiscallBase();
    void InitWrapper(uintptr_t offset, const size_t* paramSizes, int paramCount, size_t returnParamSize);
};

template<class T>
class FunctionOffsetThiscall final : public _Get_function_impl<T>::type,
                                     public _Get_function_impl_param_capture<T>::type,
                                     public FunctionOffsetThiscallBase,
                                     ILazyOffsetInitTarget
{
public:
    using FunctionOffsetThiscallBase::m_wrapper;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_return_size;
    using _Get_function_impl<T>::type::m_func;

    explicit FunctionOffsetThiscall(const OffsetValue value)
        : _Func_class_param_capture(),
          FunctionOffsetThiscallBase()
    {
        if (value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
        {
            InitWrapper(value.m_fixed_value, m_param_sizes, m_param_count, m_return_size);

            if (m_wrapper != nullptr)
                m_func = m_wrapper->GetPtr();
            else
                m_func = nullptr;
        }
        else
            OffsetManager::RegisterLazyInitialization(this, value.m_lazy_evaluation_index);
    }

    void SetLazyValue(const uintptr_t value) override
    {
        InitWrapper(value, m_param_sizes, m_param_count, m_return_size);

        if (m_wrapper != nullptr)
            m_func = m_wrapper->GetPtr();
        else
            m_func = nullptr;
    }
};

template<typename T>
// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
class FieldOffset final : ILazyOffsetInitTarget
{
public:
    // ReSharper disable once CppNonExplicitConvertingConstructor
    FieldOffset(uintptr_t ptr)
        : m_ptr(reinterpret_cast<T*>(ptr))
    {
    }

    // ReSharper disable once CppNonExplicitConvertingConstructor
    FieldOffset(OffsetValue offset)
    {
        if (offset.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
        {
            m_ptr = reinterpret_cast<T*>(offset.m_fixed_value);
        }
        else
        {
            m_ptr = nullptr;
            OffsetManager::RegisterLazyInitialization(this, offset.m_lazy_evaluation_index);
        }
    }

    void SetLazyValue(uintptr_t value) override
    {
        m_ptr = reinterpret_cast<T*>(value);
    }

    T* Ptr() const
    {
        return m_ptr;
    }

    T& operator()() const
    {
        assert(m_ptr != nullptr);
        return *m_ptr;
    }

    T& operator*() const
    {
        assert(m_ptr != nullptr);
        return *m_ptr;
    }

    T* operator->() const
    {
        assert(m_ptr != nullptr);
        return m_ptr;
    }

    T& operator[](const int index) const
    {
        assert(m_ptr != nullptr);
        return m_ptr[index];
    }

private:
    T* m_ptr;
};
