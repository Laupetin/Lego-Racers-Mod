#pragma once
#include <string>

class Component
{
public:
    virtual ~Component() = default;
    Component(const Component& other) = default;
    Component(Component&& other) noexcept = default;
    Component& operator=(const Component& other) = default;
    Component& operator=(Component&& other) noexcept = default;

    void Install();

protected:
    explicit Component(std::string name);

    virtual bool InstallInternal() = 0;

private:
    std::string m_name;
};
