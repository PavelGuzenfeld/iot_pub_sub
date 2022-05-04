#include "iot_controller.hpp"

namespace iot
{

Controller::Controller(Attributes const& a_attributes, DevicePtr a_device)
:   m_attributes(a_attributes)
,   m_device(std::move(a_device))
{

}

Event Controller::store(Event const& a_event)
{
    m_eventBacklog.add(a_event);
    return {a_event.m_eventType + "stored"};
}

Event Controller::handle()
{
    return {};
}

Event Controller::probe()
{
    return {};
}

}   //namespace iot

