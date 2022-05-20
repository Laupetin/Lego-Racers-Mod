#pragma once

#include <cstdint>

#include "CallDetails.h"
#include "IAsmWrapper.h"
#include "FunctionLike.h"
#include "UsercallConfiguration.h"

class DetourBase
{
public:
    enum class DetourType
    {
        JUMP,
        CALL
    };

private:
    bool m_installed;
    std::unique_ptr<uint8_t[]> m_original_data;
    size_t m_original_data_size;

protected:
    uintptr_t m_address;
    void* m_detour_func_ptr;

    DetourBase();
    explicit DetourBase(uintptr_t address);
    DetourBase(uintptr_t address, void* detourFuncPtr);

    void Install(DetourType type);

public:
    ~DetourBase();
    DetourBase(const DetourBase& other) = delete;
    DetourBase(DetourBase&& other) noexcept;
    DetourBase& operator=(const DetourBase& other) = delete;
    DetourBase& operator=(DetourBase&& other) noexcept;
};

class DetourTrampolineBase : public DetourBase
{
protected:
    std::unique_ptr<IAsmWrapper> m_trampoline;

    DetourTrampolineBase();
    DetourTrampolineBase(uintptr_t address, void* detourFuncPtr);

    void BuildTrampoline();

public:
    ~DetourTrampolineBase();
    DetourTrampolineBase(const DetourTrampolineBase& other) = delete;
    DetourTrampolineBase(DetourTrampolineBase&& other) noexcept = default;
    DetourTrampolineBase& operator=(const DetourTrampolineBase& other) = delete;
    DetourTrampolineBase& operator=(DetourTrampolineBase&& other) noexcept = default;
};

class DetourUsercallBase : public DetourBase
{
protected:
    std::unique_ptr<IAsmWrapper> m_wrapper;

    DetourUsercallBase();
    explicit DetourUsercallBase(uintptr_t address);

    void InitWrapper(const void* userFunc, const size_t* paramSizes, int paramCount, size_t returnParamSize,
                     const UsercallConfiguration& usercallConfiguration, CallingConvention callingConvention);

public:
    ~DetourUsercallBase();
    DetourUsercallBase(const DetourUsercallBase& other) = delete;
    DetourUsercallBase(DetourUsercallBase&& other) noexcept = default;
    DetourUsercallBase& operator=(const DetourUsercallBase& other) = delete;
    DetourUsercallBase& operator=(DetourUsercallBase&& other) noexcept = default;
};

class DetourTrampolineUsercallBase : public DetourUsercallBase
{
protected:
    std::unique_ptr<IAsmWrapper> m_trampoline_wrapper;
    std::unique_ptr<IAsmWrapper> m_trampoline;

    DetourTrampolineUsercallBase();
    explicit DetourTrampolineUsercallBase(uintptr_t address);

    void BuildTrampoline(const size_t* paramSizes, int paramCount, size_t returnParamSize,
                         const UsercallConfiguration& usercallConfiguration, CallingConvention callingConvention);

public:
    ~DetourTrampolineUsercallBase();
    DetourTrampolineUsercallBase(const DetourTrampolineUsercallBase& other) = delete;
    DetourTrampolineUsercallBase(DetourTrampolineUsercallBase&& other) noexcept = default;
    DetourTrampolineUsercallBase& operator=(const DetourTrampolineUsercallBase& other) = delete;
    DetourTrampolineUsercallBase& operator=(DetourTrampolineUsercallBase&& other) noexcept = default;
};

template <typename T>
class FunctionDetour : public DetourBase
{
public:
    FunctionDetour()
    {
    }

    FunctionDetour(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourBase(address, reinterpret_cast<void*>(detourFunc))
    {
        Install(DetourType::JUMP);
    }

    ~FunctionDetour() = default;
    FunctionDetour(const FunctionDetour& other) = delete;
    FunctionDetour(FunctionDetour&& other) noexcept = default;
    FunctionDetour& operator=(const FunctionDetour& other) = delete;
    FunctionDetour& operator=(FunctionDetour&& other) noexcept = default;

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        m_detour_func_ptr = reinterpret_cast<void*>(detourFunc);
        Install(DetourType::JUMP);
    }
};

template <typename T>
class FunctionDetourUsercall : public _Get_function_impl_param_capture<T>::type, public DetourUsercallBase
{
public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    FunctionDetourUsercall()
    {
    }

    FunctionDetourUsercall(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
                           typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::JUMP);
    }

    ~FunctionDetourUsercall() = default;
    FunctionDetourUsercall(const FunctionDetourUsercall& other) = delete;
    FunctionDetourUsercall(FunctionDetourUsercall&& other) noexcept = default;
    FunctionDetourUsercall& operator=(const FunctionDetourUsercall& other) = delete;
    FunctionDetourUsercall& operator=(FunctionDetourUsercall&& other) noexcept = default;

    void Init(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
              typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::JUMP);
    }
};

template <typename T>
class FunctionDetourThiscall : public _Get_function_impl_param_capture<T>::type, public DetourUsercallBase
{
public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    FunctionDetourThiscall()
    {
    }

    FunctionDetourThiscall(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    UsercallConfiguration().FirstParameter().InEcx(), CallingConvention::C_THISCALL);
        Install(DetourType::JUMP);
    }

    ~FunctionDetourThiscall() = default;
    FunctionDetourThiscall(const FunctionDetourThiscall& other) = delete;
    FunctionDetourThiscall(FunctionDetourThiscall&& other) noexcept = default;
    FunctionDetourThiscall& operator=(const FunctionDetourThiscall& other) = delete;
    FunctionDetourThiscall& operator=(FunctionDetourThiscall&& other) noexcept = default;

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    UsercallConfiguration().FirstParameter().InEcx(), CallingConvention::C_THISCALL);
        Install(DetourType::JUMP);
    }
};

template <typename T>
class FunctionDetourTrampoline : public _Get_function_impl<T>::type, public DetourTrampolineBase
{
    using _Get_function_impl<T>::type::m_func;

public:
    FunctionDetourTrampoline()
    {
    }

    FunctionDetourTrampoline(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourTrampolineBase(address, reinterpret_cast<void*>(detourFunc))
    {
        BuildTrampoline();
        m_func = m_trampoline->GetPtr();
        Install(DetourType::JUMP);
    }

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        m_detour_func_ptr = reinterpret_cast<void*>(detourFunc);
        BuildTrampoline();
        m_func = m_trampoline->GetPtr();
        Install(DetourType::JUMP);
    }
};

template <typename T>
class FunctionDetourTrampolineUsercall : public _Get_function_impl<T>::type,
                                         public _Get_function_impl_param_capture<T>::type,
                                         public DetourTrampolineUsercallBase
{
    using _Get_function_impl<T>::type::m_func;

public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    FunctionDetourTrampolineUsercall()
    {
    }

    FunctionDetourTrampolineUsercall(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
                                     typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        BuildTrampoline(m_param_sizes, m_param_count, m_return_size, usercallConfiguration, CallingConvention::C_CDECL);
        m_func = m_trampoline_wrapper->GetPtr();
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::JUMP);
    }

    ~FunctionDetourTrampolineUsercall() = default;
    FunctionDetourTrampolineUsercall(const FunctionDetourTrampolineUsercall& other) = delete;
    FunctionDetourTrampolineUsercall(FunctionDetourTrampolineUsercall&& other) noexcept = default;
    FunctionDetourTrampolineUsercall& operator=(const FunctionDetourTrampolineUsercall& other) = delete;
    FunctionDetourTrampolineUsercall& operator=(FunctionDetourTrampolineUsercall&& other) noexcept = default;

    void Init(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
              typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        BuildTrampoline(m_param_sizes, m_param_count, m_return_size, usercallConfiguration, CallingConvention::C_CDECL);
        m_func = m_trampoline_wrapper->GetPtr();
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::JUMP);
    }
};

template <typename T>
class FunctionDetourTrampolineThiscall : public _Get_function_impl<T>::type,
                                         public _Get_function_impl_param_capture<T>::type,
                                         public DetourTrampolineUsercallBase
{
    using _Get_function_impl<T>::type::m_func;

public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    FunctionDetourTrampolineThiscall()
    {
    }

    FunctionDetourTrampolineThiscall(const uintptr_t address,
                                     typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        UsercallConfiguration configuration;
        configuration.FirstParameter().InEcx();

        BuildTrampoline(m_param_sizes, m_param_count, m_return_size, configuration, CallingConvention::C_THISCALL);
        m_func = m_trampoline_wrapper->GetPtr();
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size, configuration,
                    CallingConvention::C_THISCALL);
        Install(DetourType::JUMP);
    }

    ~FunctionDetourTrampolineThiscall() = default;
    FunctionDetourTrampolineThiscall(const FunctionDetourTrampolineThiscall& other) = delete;
    FunctionDetourTrampolineThiscall(FunctionDetourTrampolineThiscall&& other) noexcept = default;
    FunctionDetourTrampolineThiscall& operator=(const FunctionDetourTrampolineThiscall& other) = delete;
    FunctionDetourTrampolineThiscall& operator=(FunctionDetourTrampolineThiscall&& other) noexcept = default;

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        UsercallConfiguration configuration;
        configuration.FirstParameter().InEcx();

        m_address = address;
        BuildTrampoline(m_param_sizes, m_param_count, m_return_size, configuration, CallingConvention::C_THISCALL);
        m_func = m_trampoline_wrapper->GetPtr();
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size, configuration,
                    CallingConvention::C_THISCALL);
        Install(DetourType::JUMP);
    }
};

template <typename T>
class CallDetour : public DetourBase
{
public:
    CallDetour()
    {
    }

    CallDetour(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourBase(address, reinterpret_cast<void*>(detourFunc))
    {
        Install(DetourType::CALL);
    }

    ~CallDetour() = default;
    CallDetour(const CallDetour& other) = delete;
    CallDetour(CallDetour&& other) noexcept = default;
    CallDetour& operator=(const CallDetour& other) = delete;
    CallDetour& operator=(CallDetour&& other) noexcept = default;

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        m_detour_func_ptr = reinterpret_cast<void*>(detourFunc);
        Install(DetourType::CALL);
    }
};

template <typename T>
class CallDetourUsercall : public _Get_function_impl_param_capture<T>::type, public DetourUsercallBase
{
public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    CallDetourUsercall()
    {
    }

    CallDetourUsercall(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
                       typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::CALL);
    }

    ~CallDetourUsercall() = default;
    CallDetourUsercall(const CallDetourUsercall& other) = delete;
    CallDetourUsercall(CallDetourUsercall&& other) noexcept = default;
    CallDetourUsercall& operator=(const CallDetourUsercall& other) = delete;
    CallDetourUsercall& operator=(CallDetourUsercall&& other) noexcept = default;

    void Init(const uintptr_t address, const UsercallConfiguration usercallConfiguration,
              typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    usercallConfiguration, CallingConvention::C_CDECL);
        Install(DetourType::CALL);
    }
};

template <typename T>
class CallDetourThiscall : public _Get_function_impl_param_capture<T>::type, public DetourUsercallBase
{
public:
    using _Get_function_impl_param_capture<T>::type::func_ptr_t;
    using ParamCaptureFunc::m_param_sizes;
    using ParamCaptureFunc::m_param_count;
    using ParamCaptureFunc::m_return_size;

    CallDetourThiscall()
    {
    }

    CallDetourThiscall(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
        : DetourUsercallBase(address)
    {
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    UsercallConfiguration().FirstParameter().InEcx(), CallingConvention::C_THISCALL);
        Install(DetourType::CALL);
    }

    ~CallDetourThiscall() = default;
    CallDetourThiscall(const CallDetourThiscall& other) = delete;
    CallDetourThiscall(CallDetourThiscall&& other) noexcept = default;
    CallDetourThiscall& operator=(const CallDetourThiscall& other) = delete;
    CallDetourThiscall& operator=(CallDetourThiscall&& other) noexcept = default;

    void Init(const uintptr_t address, typename _Get_function_impl<T>::type::func_ptr_t detourFunc)
    {
        m_address = address;
        InitWrapper(reinterpret_cast<void*>(detourFunc), m_param_sizes, m_param_count, m_return_size,
                    UsercallConfiguration().FirstParameter().InEcx(), CallingConvention::C_THISCALL);
        Install(DetourType::CALL);
    }
};
