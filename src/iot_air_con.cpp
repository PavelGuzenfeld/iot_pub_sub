#include <string>
#include <iostream>
#include "iot_device_api.hpp"

struct AirCon : public iot::Controller<std::string>
{
    AirCon(std::string const& a_config)
    {
        std::cout << a_config << "\n";
    }

    std::string handle(std::string const& a_eventData)
    {
        return std::string() + "handled - " + a_eventData;
    }
};
