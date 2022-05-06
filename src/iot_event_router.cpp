#include "iot_event_router.hpp"

namespace iot
{

EventRouter::EventRouter(CONTAINER& a_subs)
:   m_subs(a_subs)
{

}

void EventRouter::rout(EVENT const& a_event)
{
    auto subscribed = m_subs.find(a_event.m_eventType);
    if(subscribed == m_subs.end())
    {
        return;
    }

    auto& devices = subscribed->second;
    for(auto& d: devices)
    {
        d.consume(a_event);
    }
}

}   //namespace iot