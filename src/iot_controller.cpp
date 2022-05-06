#include "iot_controller.hpp"
#include "iot_utils.hpp"

namespace iot
{

Controller::Controller(Attributes const& a_attributes, DevicePtr a_device)
:   m_attributes(a_attributes)
,   m_device(a_device)
{

}

Event Controller::store(Event const& a_event)
{
    m_eventBacklog.add(a_event);
    return response(m_attributes, "stored");
}

Event Controller::handle()
{
    Event returnEvent;
    auto Handlinglambda = [&](Event const& a_event)
    {
       auto data = m_device->handle(a_event.m_data);
       returnEvent = response(m_attributes, data);
    };
    m_eventBacklog.remove(Handlinglambda);
    return returnEvent;
}

Event Controller::probe()
{
    auto data = m_device->probe();
    return response(m_attributes, data);
}

}   //namespace iot

