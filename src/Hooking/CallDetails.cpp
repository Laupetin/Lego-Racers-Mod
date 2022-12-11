#include "CallDetails.h"

#include "Offset.h"

CallDetails::CallDetails(const CallingConvention callingConvention)
{
    m_compiler = TrampolineGlobals::Instance().GetTargetCompiler();
    m_calling_convention = callingConvention;
}

CallDetails::CallDetails(const TargetCompiler compiler, const CallingConvention callingConvention)
{
    m_compiler = compiler;
    m_calling_convention = callingConvention;
}
