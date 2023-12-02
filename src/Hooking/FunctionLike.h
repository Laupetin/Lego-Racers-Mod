#pragma once

#include <functional>

// CLASS TEMPLATE _Func_class
template<class _Ret, class... _Types> class _Func_class
{
protected:
    void* m_func;

public:
    using func_ptr_t = _Ret (*)(_Types...);
    using ret_t = _Ret;

    _Func_class()
        : m_func(nullptr)
    {
    }

    _Ret operator()(_Types... args) const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return static_cast<func_ptr_t>(m_func)(args...);
    }

    func_ptr_t Ptr() const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return m_func;
    }

    [[nodiscard]] uintptr_t Addr() const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return reinterpret_cast<uintptr_t>(m_func);
    }
};

template<class _Ret, class... _Types> class _Func_class_stdcall
{
protected:
    void* m_func;

public:
    using func_ptr_t = _Ret(__stdcall*)(_Types...);
    using ret_t = _Ret;

    _Func_class_stdcall()
        : m_func(nullptr)
    {
    }

    _Ret operator()(_Types... args) const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return static_cast<func_ptr_t>(m_func)(args...);
    }

    func_ptr_t Ptr() const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return m_func;
    }

    [[nodiscard]] uintptr_t Addr() const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return reinterpret_cast<uintptr_t>(m_func);
    }
};

template<class _Ret, class... _Types> class _Func_class_varargs
{
protected:
    void* m_func;

public:
    using func_ptr_t = _Ret (*)(_Types..., ...);
    using ret_t = _Ret;

    _Func_class_varargs()
        : m_func(nullptr)
    {
    }

    template<class... _Var_Types> _Ret operator()(_Types... args, _Var_Types... varArgs) const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return static_cast<func_ptr_t>(m_func)(args..., varArgs...);
    }

    func_ptr_t Ptr() const
    {
        if (m_func == nullptr)
            throw std::exception("Tried accessing uninitialized function offset.");

        return m_func;
    }
};

template<typename T> struct _Return_param_size
{
    static constexpr size_t SIZE = sizeof T;
};

template<> struct _Return_param_size<void>
{
    static constexpr size_t SIZE = 0;
};

class ParamCaptureFunc
{
protected:
    const size_t* m_param_sizes;
    const int m_param_count;
    const size_t m_return_size;

    ParamCaptureFunc(const size_t* paramSizes, int paramCount, size_t returnSize);

public:
    ParamCaptureFunc(const ParamCaptureFunc& other) = default;
    ParamCaptureFunc(ParamCaptureFunc&& other) noexcept = default;
    ParamCaptureFunc& operator=(const ParamCaptureFunc& other);
    ParamCaptureFunc& operator=(ParamCaptureFunc&& other) noexcept;
};

// CLASS TEMPLATE _Func_class
template<class _Ret, class... _Types> class _Func_class_param_capture : public ParamCaptureFunc
{
    const size_t m_param_sizes_array[sizeof...(_Types)]{sizeof(_Types)...};

public:
    using func_ptr_t = _Ret (*)(_Types..., ...);
    using ret_t = _Ret;

    _Func_class_param_capture()
        : ParamCaptureFunc(m_param_sizes_array, sizeof...(_Types), _Return_param_size<_Ret>::SIZE)
    {
    }

    _Func_class_param_capture(const _Func_class_param_capture& other) = default;
    _Func_class_param_capture(_Func_class_param_capture&& other) noexcept = default;

    _Func_class_param_capture& operator=(const _Func_class_param_capture& other)
    {
        if (this == &other)
            return *this;
        ParamCaptureFunc::operator=(other);
        return *this;
    }

    _Func_class_param_capture& operator=(_Func_class_param_capture&& other) noexcept
    {
        if (this == &other)
            return *this;
        ParamCaptureFunc::operator=(std::move(other));
        return *this;
    }
};

// STRUCT TEMPLATE _Get_function_impl
template<class T> struct _Get_function_impl;

#define _GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)                                                                                                               \
    template<class _Ret, class... _Types> struct _Get_function_impl<_Ret CALL_OPT(_Types...)> /* determine type from argument list */                          \
    {                                                                                                                                                          \
        using type = _Func_class<_Ret, _Types...>;                                                                                                             \
    };

_NON_MEMBER_CALL(_GET_FUNCTION_IMPL, X1, X2, X3)
#undef _GET_FUNCTION_IMPL

// STRUCT TEMPLATE _Get_function_impl_param_capture
template<class T> struct _Get_function_impl_param_capture;

#define _GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)                                                                                                               \
    template<class _Ret, class... _Types> struct _Get_function_impl_param_capture<_Ret CALL_OPT(_Types...)> /* determine type from argument list */            \
    {                                                                                                                                                          \
        using type = _Func_class_param_capture<_Ret, _Types...>;                                                                                               \
    };

_NON_MEMBER_CALL(_GET_FUNCTION_IMPL, X1, X2, X3)
#undef _GET_FUNCTION_IMPL

// STRUCT TEMPLATE _Get_function_impl_stdcall
template<class T> struct _Get_function_impl_stdcall;

#define _GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)                                                                                                               \
    template<class _Ret, class... _Types> struct _Get_function_impl_stdcall<_Ret CALL_OPT(_Types...)> /* determine type from argument list */                  \
    {                                                                                                                                                          \
        using type = _Func_class_stdcall<_Ret, _Types...>;                                                                                                     \
    };

_NON_MEMBER_CALL(_GET_FUNCTION_IMPL, X1, X2, X3)
#undef _GET_FUNCTION_IMPL

// STRUCT TEMPLATE _Get_function_impl_var_args
template<class T> struct _Get_function_impl_varargs;

#define _GET_FUNCTION_IMPL(CALL_OPT, X1, X2, X3)                                                                                                               \
    template<class _Ret, class... _Types> struct _Get_function_impl_varargs<_Ret CALL_OPT(_Types...)> /* determine type from argument list */                  \
    {                                                                                                                                                          \
        using type = _Func_class_varargs<_Ret, _Types...>;                                                                                                     \
    };

_NON_MEMBER_CALL(_GET_FUNCTION_IMPL, X1, X2, X3)
#undef _GET_FUNCTION_IMPL
