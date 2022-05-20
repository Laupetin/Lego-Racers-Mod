#pragma once

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <mutex>

#include "FunctionLike.h"
#include "CallDetails.h"
#include "Singleton.h"
#include "StackToRegisterWrapperBuilder.h"
#include "UsercallConfiguration.h"

class BaseOffset;

class OffsetManager : public Singleton<OffsetManager>
{
    friend class BaseOffset;

    std::mutex m_offset_mutex;
    std::vector<BaseOffset*> m_offsets;
    TargetCompiler m_compiler = TargetCompiler::UNKNOWN;

    void AddOffset(BaseOffset* offset);

public:
    TargetCompiler GetTargetCompiler() const;
    void SetTargetCompiler(TargetCompiler targetCompiler);

    void AssertOffsetCount(int offsetCount);
    void InitAll(int offsetIndex);
};

class BaseOffset
{
protected:
    std::vector<uintptr_t> m_offsets;
    void* m_offset;

public:
    BaseOffset(std::initializer_list<uintptr_t> offsets);
    virtual ~BaseOffset() = default;
    BaseOffset(const BaseOffset& other) = delete;
    BaseOffset(BaseOffset&& other) noexcept = delete;
    BaseOffset& operator=(const BaseOffset& other) = delete;
    BaseOffset& operator=(BaseOffset&& other) noexcept = delete;

    virtual void Init(int offsetIndex);
    virtual bool IsInitialized();
    virtual int OffsetCount();
};

template <typename T>
class FieldOffset final : public BaseOffset
{
public:
    FieldOffset(const std::initializer_list<uintptr_t> offsets)
        : BaseOffset(offsets)
    {
    }

    T& operator*()
    {
        if (m_offset == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return *static_cast<T*>(m_offset);
    }

    T& operator->()
    {
        if (m_offset == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return *static_cast<T*>(m_offset);
    }

    T* Ptr() const
    {
        if (m_offset == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return static_cast<T*>(m_offset);
    }
};

template <class T>
class FunctionOffset final : public _Get_function_impl<T>::type, public BaseOffset
{
public:
    using BaseOffset::m_offset;
    using _Get_function_impl<T>::type::m_func;

    FunctionOffset(const std::initializer_list<uintptr_t> offsets)
        : _Get_function_impl<T>::type(),
          BaseOffset(offsets)
    {
    }

    void Init(const int offsetIndex) override
    {
        BaseOffset::Init(offsetIndex);
        m_func = m_offset;
    }
};

template <class T>
class FunctionOffsetVarArgs final : public _Get_function_impl_varargs<T>::type, public BaseOffset
{
public:
    using BaseOffset::m_offset;
    using _Get_function_impl_varargs<T>::type::m_func;

    FunctionOffsetVarArgs(const std::initializer_list<uintptr_t> offsets)
        : _Get_function_impl_varargs<T>::type(),
          BaseOffset(offsets)
    {
    }

    void Init(const int offsetIndex) override
    {
        BaseOffset::Init(offsetIndex);
        m_func = m_offset;
    }
};

class FunctionOffsetUsercallBase : public BaseOffset
{
protected:
    std::unique_ptr<IAsmWrapper> m_wrapper;
    std::unique_ptr<UsercallConfiguration> m_usercall_configuration;
    std::function<void(UsercallConfiguration& usercall, int offsetIndex)> m_usercall_init;

    FunctionOffsetUsercallBase(std::initializer_list<uintptr_t> offsets,
                               std::function<void(UsercallConfiguration& usercall, int offsetIndex)>
                               usercallInit);
    void InitWrapper(int offsetIndex, const size_t* paramSizes, int paramCount, size_t returnParamSize);
};

template <class T>
class FunctionOffsetUsercall final : public _Get_function_impl<T>::type, public _Get_function_impl_param_capture<T>::type, public FunctionOffsetUsercallBase
{
public:
    using FunctionOffsetUsercallBase::m_wrapper;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;
    using _Get_function_impl<T>::type::m_func;

    FunctionOffsetUsercall(const std::initializer_list<uintptr_t> offsets,
                           const std::function<void(UsercallConfiguration& usercall, int offsetIndex)>
                           usercallInit)
        : _Func_class_param_capture(),
          FunctionOffsetUsercallBase(offsets, usercallInit)
    {
    }

    void Init(const int offsetIndex) override
    {
        InitWrapper(offsetIndex, m_param_sizes, m_param_count, m_return_size);

        if (m_wrapper != nullptr)
            m_func = m_wrapper->GetPtr();
        else
            m_func = m_offset;
    }
};

class FunctionOffsetThiscallBase : public BaseOffset
{
protected:
    std::unique_ptr<IAsmWrapper> m_wrapper;
    std::unique_ptr<UsercallConfiguration> m_usercall_configuration;

    FunctionOffsetThiscallBase(std::initializer_list<uintptr_t> offsets);
    void InitWrapper(int offsetIndex, const size_t* paramSizes, int paramCount, size_t returnParamSize);
};

template <class T>
class FunctionOffsetThiscall final : public _Get_function_impl<T>::type, public _Get_function_impl_param_capture<T>::type, public FunctionOffsetThiscallBase
{
public:
    using FunctionOffsetThiscallBase::m_wrapper;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;
    using _Get_function_impl<T>::type::m_func;

    FunctionOffsetThiscall(const std::initializer_list<uintptr_t> offsets)
        : _Func_class_param_capture(),
          FunctionOffsetThiscallBase(offsets)
    {
    }

    void Init(const int offsetIndex) override
    {
        InitWrapper(offsetIndex, m_param_sizes, m_param_count, m_return_size);

        if (m_wrapper != nullptr)
            m_func = m_wrapper->GetPtr();
        else
            m_func = m_offset;
    }
};
