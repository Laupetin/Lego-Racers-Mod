#pragma once

#include "patch/OffsetBase.h"

class Offset : public OffsetBase<2>
{
public:
    /*OffsetValue m_value;

    Offset()
    {
    }

    Offset& Racers99(const uintptr_t value)
    {
        auto& storage = OffsetManagerStorage<ENV_COUNT>::Instance();
        if (!storage.IsAnyEnvironmentSelected())
        {
            if (m_value.m_lazy_evaluation_index == OffsetValue::NO_LAZY_EVALUATION)
                m_value.m_lazy_evaluation_index = storage.ReserveLazyLookupIndex();
            storage.SetLazyLookupValue(m_value.m_lazy_evaluation_index, 0, value);
        }
        else if(storage.GetSelectedEnvironment() == 0)
        {
            m_value.m_fixed_value = value;
        }

        return *this;
    }

    Offset& Racers01(uintptr_t value)
    {
        return *this;
    }*/
    OFFSET_ENV(0, Racers99)
    OFFSET_ENV(1, Racers01)
};
