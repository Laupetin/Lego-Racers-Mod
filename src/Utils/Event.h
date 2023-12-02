#pragma once

#include <functional>
#include <vector>

template<class... Types> class Event
{
public:
    void RegisterCallback(std::function<bool(Types...)> cb)
    {
        m_callbacks.emplace_back(std::move(cb));
    }

    void operator()(Types... args) const
    {
        for (const auto& cb : m_callbacks)
        {
            const auto result = cb(args...);
            if (!result)
                return;
        }
    }

private:
    std::vector<std::function<bool(Types...)>> m_callbacks;
};
