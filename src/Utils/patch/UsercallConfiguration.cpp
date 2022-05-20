#include "UsercallConfiguration.h"

UsercallConfiguration::ParameterConfiguration::ParameterConfiguration(UsercallConfiguration& usercallConfiguration)
    : m_usercall_configuration(usercallConfiguration),
      m_location(Register::INVALID)
{
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEax()
{
    m_location = Register::EAX;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEbx()
{
    m_location = Register::EBX;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEcx()
{
    m_location = Register::ECX;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEdx()
{
    m_location = Register::EDX;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEsi()
{
    m_location = Register::ESI;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration& UsercallConfiguration::ParameterConfiguration::InEdi()
{
    m_location = Register::EDI;
    m_usercall_configuration.ApplyParameter();
    return m_usercall_configuration;
}

UsercallConfiguration::ParameterLocation::ParameterLocation()
    : m_register(Register::INVALID),
      m_parameter_index(0)
{
}

UsercallConfiguration::ParameterLocation::ParameterLocation(const Register _register, const int parameterIndex)
    : m_register(_register),
      m_parameter_index(parameterIndex)
{
}

UsercallConfiguration::UsercallConfiguration()
    : m_parameter(*this),
      m_parameter_index(0)
{
}

void UsercallConfiguration::ApplyParameter()
{
    if (m_parameter.m_location != Register::INVALID)
    {
        bool existingParameterUsed = false;

        for (auto& parameterLocation : m_parameter_locations)
        {
            if (parameterLocation.m_parameter_index == m_parameter_index)
            {
                parameterLocation.m_register = m_parameter.m_location;
                existingParameterUsed = true;
                break;
            }
        }

        if(!existingParameterUsed)
            m_parameter_locations.emplace_back(m_parameter.m_location, m_parameter_index);
    }

    m_parameter_index++;
}

UsercallConfiguration::ParameterConfiguration& UsercallConfiguration::FirstParameter()
{
    m_parameter_index = 0;
    m_parameter.m_location = Register::INVALID;
    return m_parameter;
}

UsercallConfiguration::ParameterConfiguration& UsercallConfiguration::NextParameter()
{
    m_parameter.m_location = Register::INVALID;
    return m_parameter;
}

UsercallConfiguration::ParameterConfiguration& UsercallConfiguration::ParameterIndex(const int index)
{
    m_parameter_index = index;
    m_parameter.m_location = Register::INVALID;
    return m_parameter;
}
