#ifndef IOT_DEVICE_API_HPP
#define IOT_DEVICE_API_HPP

#include "abstract.hpp"
#include "iot_types.hpp"

namespace iot
{

struct Device : public cpp::Abstract
{
    Device() = default;
    virtual String handle(String const& a_eventData);
    virtual String probe();
};

}   //namespace iot

#endif //IOT_DEVICE_API_HPP