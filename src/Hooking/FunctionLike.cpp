#include "FunctionLike.h"

ParamCaptureFunc::ParamCaptureFunc(const size_t* paramSizes, const int paramCount, const size_t returnSize)
    : m_param_sizes(paramSizes),
      m_param_count(paramCount),
      m_return_size(returnSize)
{
}

ParamCaptureFunc& ParamCaptureFunc::operator=(const ParamCaptureFunc& other)
{
    if (this == &other)
        return *this;
    return *this;
}

ParamCaptureFunc& ParamCaptureFunc::operator=(ParamCaptureFunc&& other) noexcept
{
    if (this == &other)
        return *this;
    return *this;
}
