#include "Offset.h"

void OffsetManager::AddOffset(BaseOffset* offset)
{
    std::scoped_lock<std::mutex> lock(m_offset_mutex);

    m_offsets.push_back(offset);
}

TargetCompiler OffsetManager::GetTargetCompiler() const
{
    return m_compiler;
}

void OffsetManager::SetTargetCompiler(const TargetCompiler targetCompiler)
{
    m_compiler = targetCompiler;
}

void OffsetManager::AssertOffsetCount(const int offsetCount)
{
    for (auto* offset : m_offsets)
    {
        if (offset->OffsetCount() != offsetCount)
            throw std::exception("Invalid offset count");
    }
}

void OffsetManager::InitAll(const int offsetIndex)
{
    std::scoped_lock<std::mutex> lock(m_offset_mutex);

    for (auto* offset : m_offsets)
    {
        offset->Init(offsetIndex);
    }
}

BaseOffset::BaseOffset(const std::initializer_list<uintptr_t> offsets)
    : m_offsets(offsets),
      m_offset(nullptr)
{
    OffsetManager::Instance().AddOffset(this);
}

void BaseOffset::Init(const int offsetIndex)
{
    if (offsetIndex < 0 || static_cast<unsigned>(offsetIndex) >= m_offsets.size())
        throw std::exception("Invalid offset index");

    m_offset = reinterpret_cast<void*>(m_offsets[offsetIndex]);
}

bool BaseOffset::IsInitialized()
{
    return m_offset == nullptr;
}

int BaseOffset::OffsetCount()
{
    return m_offsets.size();
}

FunctionOffsetUsercallBase::FunctionOffsetUsercallBase(const std::initializer_list<uintptr_t> offsets,
                                                       std::function<void(
                                                           UsercallConfiguration& usercall,
                                                           int offsetIndex)> usercallInit)
    : BaseOffset(offsets),
      m_wrapper(nullptr),
      m_usercall_configuration(nullptr),
      m_usercall_init(std::move(usercallInit))
{
}

void FunctionOffsetUsercallBase::InitWrapper(const int offsetIndex, const size_t* paramSizes,
                                             const int paramCount, const size_t returnParamSize)
{
    BaseOffset::Init(offsetIndex);

    if (m_usercall_init == nullptr)
        throw std::exception(
            "Usercall must have a valid init function. If there's no configuration to be made consider using a FunctionOffset instead.");

    m_usercall_configuration = std::make_unique<UsercallConfiguration>();
    m_usercall_init(*m_usercall_configuration, offsetIndex);

    m_wrapper = StackToRegisterWrapperBuilder::BuildWrapper(m_offset, *m_usercall_configuration, paramSizes,
                                                            paramCount, CallDetails(MY_COMPILER, MY_CALLING_CONVENTION),
                                                            CallDetails(CallingConvention::C_CDECL));
}

FunctionOffsetThiscallBase::FunctionOffsetThiscallBase(const std::initializer_list<uintptr_t> offsets)
    : BaseOffset(offsets),
      m_wrapper(nullptr),
      m_usercall_configuration(nullptr)
{
}

void FunctionOffsetThiscallBase::InitWrapper(const int offsetIndex, const size_t* paramSizes,
                                             const int paramCount, const size_t returnParamSize)
{
    BaseOffset::Init(offsetIndex);

    m_usercall_configuration = std::make_unique<UsercallConfiguration>();
    m_usercall_configuration->FirstParameter().InEcx();

    m_wrapper = StackToRegisterWrapperBuilder::BuildWrapper(m_offset, *m_usercall_configuration, paramSizes,
                                                            paramCount,
                                                            CallDetails(MY_COMPILER, MY_CALLING_CONVENTION),
                                                            CallDetails(CallingConvention::C_THISCALL));
}
