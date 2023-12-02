#pragma once

enum class TargetCompiler
{
    UNKNOWN,
    MSVC,
    GCC,
    CLANG
};

enum class CallingConvention
{
    C_CDECL,
    C_THISCALL,
    C_STDCALL
};

#if defined(_MSC_VER)
constexpr TargetCompiler MY_COMPILER = TargetCompiler::MSVC;
constexpr CallingConvention MY_CALLING_CONVENTION = CallingConvention::C_CDECL;
#elif defined(__clang__)
constexpr TargetCompiler MY_COMPILER = TargetCompiler::CLANG;
constexpr CallingConvention MY_CALLING_CONVENTION = CallingConvention::C_CDECL;
#elif defined(__GNUC__)
constexpr TargetCompiler MY_COMPILER = TargetCompiler::GCC;
constexpr CallingConvention MY_CALLING_CONVENTION = CallingConvention::C_CDECL;
#elif defined(__GNUC__)
constexpr TargetCompiler MY_COMPILER = TargetCompiler::UNKNOWN;
constexpr CallingConvention MY_CALLING_CONVENTION = CallingConvention::C_CDECL;
#endif

class OffsetManager;

class CallDetails
{
public:
    TargetCompiler m_compiler;
    CallingConvention m_calling_convention;

    explicit CallDetails(CallingConvention callingConvention);
    CallDetails(TargetCompiler compiler, CallingConvention callingConvention);
};
