#include <iostream>
#include "iot_device_api.hpp"

namespace iot
{

struct AirCon : public Device
{
    AirCon(String const& a_config)
    {
        std::cout << a_config << "\n";
    }

    String handle(String const& a_eventData)
    {
        return "handled - " + a_eventData;
    }

    String probe()
    {
        return "probed";
    }
};

}   //namespace iot
