#include "Component.h"

#include <Windows.h>
#include <iostream>
#include <sstream>

Component::Component(std::string name)
    : m_name(std::move(name))
{
}

void Component::Install()
{
    if (this->InstallInternal())
    {
        std::cout << "Successfully installed component \"" << m_name << "\"\n";
    }
    else
    {
        std::ostringstream ss;
        ss << "Failed to install component \"" << m_name << "\". Now terminating.";
        MessageBoxA(nullptr, ss.str().c_str(), "Failed to install component", MB_OK | MB_ICONERROR);
        exit(1);
    }
}
