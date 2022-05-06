#include "iot_event_router.hpp"

namespace iot
{

EventRouter::EventRouter(Subscriptions& a_subs)
:   m_subs(a_subs)
{

}

void EventRouter::rout(Event const& a_event)
{
    auto subscribed = m_subs.find(a_event.m_eventType);
    if(subscribed == m_subs.end())
    {
        return;
    }

    auto& devices = subscribed->second;
    for(auto& d: devices)
    {
        d.store(a_event);
    }
}

}   //namespace iot