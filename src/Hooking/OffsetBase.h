#pragma once

#include <cstddef>
#include <cassert>
#include <cstdint>
#include <limits>
#include <mutex>
#include <array>
#include <vector>

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
class ILazyOffsetInitTarget // NOLINT(clang-diagnostic-non-virtual-dtor)
{
protected:
    ILazyOffsetInitTarget() = default;

public:
    virtual void SetLazyValue(uintptr_t value) = 0;
};

class OffsetManager
{
protected:
    OffsetManager() = default;

public:
    virtual ~OffsetManager() = default;
    OffsetManager(const OffsetManager& other) = default;
    OffsetManager(OffsetManager&& other) noexcept = default;
    OffsetManager& operator=(const OffsetManager& other) = default;
    OffsetManager& operator=(OffsetManager&& other) noexcept = default;

    [[nodiscard]] virtual uintptr_t DoLookupLazy(size_t lazyEvaluationIndex) = 0;
    virtual void DoRegisterLazyInitialization(ILazyOffsetInitTarget* target, size_t lazyLookupIndex) = 0;

    static uintptr_t LookupLazy(const size_t lazyEvaluationIndex)
    {
        assert(m_manager);
        if (!m_manager)
            return 0;

        return m_manager->DoLookupLazy(lazyEvaluationIndex);
    }

    static void RegisterLazyInitialization(ILazyOffsetInitTarget* target, const size_t lazyEvaluationIndex)
    {
        assert(m_manager);
        if (!m_manager)
            return;

        return m_manager->DoRegisterLazyInitialization(target, lazyEvaluationIndex);
    }

protected:
    static inline OffsetManager* m_manager = nullptr;
};

struct LazyOffsetInitializationTarget
{
    ILazyOffsetInitTarget* m_target;
    size_t m_lazy_lookup_index;

    LazyOffsetInitializationTarget(ILazyOffsetInitTarget* target, const size_t lazyLookupIndex)
        : m_target(target),
          m_lazy_lookup_index(lazyLookupIndex)
    {
    }
};

template <size_t EnvironmentCount>
class OffsetManagerStorage final : OffsetManager
{
    static constexpr auto NO_ENVIRONMENT_SELECTED = SIZE_MAX;
    size_t m_selected_environment_index = NO_ENVIRONMENT_SELECTED;

    std::mutex m_value_mutex;
    std::vector<std::array<uintptr_t, EnvironmentCount>> m_lazy_values;

    std::mutex m_init_mutex;
    std::vector<LazyOffsetInitializationTarget> m_lazy_offset_initialization_targets;

public:
    static OffsetManagerStorage<EnvironmentCount>& Instance()
    {
        static OffsetManagerStorage<EnvironmentCount> instance;
        return instance;
    }

    OffsetManagerStorage()
    {
        m_manager = this;
    }

    [[nodiscard]] bool IsAnyEnvironmentSelected() const
    {
        return m_selected_environment_index != NO_ENVIRONMENT_SELECTED;
    }

    [[nodiscard]] size_t GetSelectedEnvironment() const
    {
        return m_selected_environment_index;
    }

    void SetSelectedEnvironment(const size_t environmentIndex)
    {
        assert(environmentIndex < EnvironmentCount);
        if (environmentIndex >= EnvironmentCount)
            return;

        std::scoped_lock lock(m_init_mutex);
        m_selected_environment_index = environmentIndex;
        for (const auto& target : m_lazy_offset_initialization_targets)
        {
            if (target.m_lazy_lookup_index >= m_lazy_values.size())
                continue;

            target.m_target->SetLazyValue(m_lazy_values[target.m_lazy_lookup_index][environmentIndex]);
        }
    }

    [[nodiscard]] uintptr_t DoLookupLazy(size_t lazyLookupIndex) override
    {
        std::scoped_lock lock(m_value_mutex);

        if (lazyLookupIndex > m_lazy_values.size())
            return 0;

        if (m_selected_environment_index == NO_ENVIRONMENT_SELECTED)
            return 0;

        return m_lazy_values[lazyLookupIndex][m_selected_environment_index];
    }

    void DoRegisterLazyInitialization(ILazyOffsetInitTarget* target, const size_t lazyLookupIndex) override
    {
        std::scoped_lock lock(m_init_mutex);

        assert(target);
        assert(lazyLookupIndex < m_lazy_values.size());
        if (lazyLookupIndex >= m_lazy_values.size())
            return;

        m_lazy_offset_initialization_targets.emplace_back(target, lazyLookupIndex);

        if (m_selected_environment_index != NO_ENVIRONMENT_SELECTED)
            target->SetLazyValue(m_lazy_values[lazyLookupIndex][m_selected_environment_index]);
    }

    [[nodiscard]] size_t ReserveLazyLookupIndex()
    {
        std::scoped_lock lock(m_value_mutex);

        const auto newIndex = m_lazy_values.size();
        m_lazy_values.emplace_back();

        return newIndex;
    }

    void SetLazyLookupValue(const size_t lazyLookupIndex, const size_t environmentIndex, const uintptr_t value)
    {
        std::scoped_lock lock(m_value_mutex);

        if (lazyLookupIndex > m_lazy_values.size() || environmentIndex >= EnvironmentCount)
            return;

        m_lazy_values[lazyLookupIndex][environmentIndex] = value;
    }
};

class OffsetValue
{
public:
    static constexpr size_t NO_LAZY_EVALUATION = SIZE_MAX;

    size_t m_lazy_evaluation_index;
    uintptr_t m_fixed_value;

    OffsetValue()
        : m_lazy_evaluation_index(NO_LAZY_EVALUATION),
          m_fixed_value(0u)
    {
    }
};

template <size_t EnvCount>
class OffsetBase
{
protected:
    static constexpr auto ENV_COUNT = EnvCount;

    OffsetValue m_value;

public:
    // ReSharper disable once CppNonExplicitConversionOperator
    operator OffsetValue() const
    {
        return m_value;
    }
};

#define OFFSET_ENV(_envIndex, _envName) \
    Offset& _envName(const uintptr_t value)                                                     \
    {                                                                                           \
        auto& storage = OffsetManagerStorage<ENV_COUNT>::Instance();                            \
        if (!storage.IsAnyEnvironmentSelected())                                                \
        {                                                                                       \
            if (m_value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)             \
                m_value.m_lazy_evaluation_index = storage.ReserveLazyLookupIndex();             \
            storage.SetLazyLookupValue(m_value.m_lazy_evaluation_index, (_envIndex), value);    \
        }                                                                                       \
        else if (storage.GetSelectedEnvironment() == (_envIndex))                               \
        {                                                                                       \
            m_value.m_fixed_value = value;                                                      \
        }                                                                                       \
                                                                                                \
        return *this;                                                                           \
    }                                                                                           \
    static void Apply##_envName()                                                               \
    {                                                                                           \
        OffsetManagerStorage<ENV_COUNT>::Instance().SetSelectedEnvironment(_envIndex); \
    }
