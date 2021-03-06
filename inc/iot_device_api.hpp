#ifndef IOT_DEVICE_API_HPP
#define IOT_DEVICE_API_HPP

#include "abstract.hpp"
#include "iot_types.hpp"

namespace iot
{

struct Device : public cpp::Abstract
{
    virtual String handle(String const& a_eventData) = 0;
    virtual String probe() = 0;
};

}   //namespace iot

#endif //IOT_DEVICE_API_HPP