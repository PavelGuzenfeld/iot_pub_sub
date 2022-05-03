#include <iostream>
#include "iot_device_api.hpp"

namespace iot
{

struct AirCon : public iot::Controller
{
    AirCon(String const& a_config)
    {
        std::cout << a_config << "\n";
    }

    String handle(String const& a_eventData)
    {
        return String() + "handled - " + a_eventData;
    }
};

}   //namespace iot
