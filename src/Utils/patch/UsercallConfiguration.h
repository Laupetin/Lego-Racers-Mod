#pragma once
#include <vector>

#include "Register.h"

class UsercallConfiguration
{
protected:
    void ApplyParameter();

public:
    class ParameterConfiguration
    {
        UsercallConfiguration& m_usercall_configuration;

    public:
        Register m_location;

        explicit ParameterConfiguration(UsercallConfiguration& usercallConfiguration);

        UsercallConfiguration& InEax();
        UsercallConfiguration& InEbx();
        UsercallConfiguration& InEcx();
        UsercallConfiguration& InEdx();
        UsercallConfiguration& InEsi();
        UsercallConfiguration& InEdi();
    };

    class ParameterLocation
    {
    public:
        Register m_register;
        int m_parameter_index;

        ParameterLocation();
        ParameterLocation(Register _register, int parameterIndex);
    };

private:
    ParameterConfiguration m_parameter;
    int m_parameter_index;

public:
    std::vector<ParameterLocation> m_parameter_locations;

    UsercallConfiguration();

    ParameterConfiguration& FirstParameter();
    ParameterConfiguration& NextParameter();
    ParameterConfiguration& ParameterIndex(int index);
};
