#ifndef IOT_AGENT_API_HPP
#define IOT_AGENT_API_HPP

#include "abstract.hpp"
#include "iot_types.hpp"

namespace iot
{

struct EventProducer : public cpp::Abstract
{
    EventProducer() = default;
    virtual Event produce() = 0;
};

struct EventHandler : public cpp::Abstract
{
    EventHandler() = default;
    virtual Event store(Event const& a_event) = 0;
    virtual Event handle() = 0;
};

}   //namespace iot

#endif  //IOT_AGENT_API_HPP