#ifndef IOT_EVENT_HANDLER_BASE_HPP
#define IOT_EVENT_HANDLER_BASE_HPP

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG>
class EventHandlerBase
{
protected:
    EventHandlerBase(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location, BACKLOG const& a_backlog);
    virtual void consumeEvent(EVENT const& a_event) = 0;
    virtual EVENT handleEvent() = 0;

protected:
    STRING m_eventType;
    STRING m_id;
    STRING m_type;
    LOCATION m_location;
    BACKLOG m_backlog;
};

}   //namespace iot

#include "inl/iot_event_handler_base.hxx"

#endif // IOT_EVENT_HANDLER_BASE_HPP