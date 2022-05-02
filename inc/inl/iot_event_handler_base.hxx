#ifndef IOT_EVENT_HANDLER_BASE_HXX
#define IOT_EVENT_HANDLER_BASE_HXX

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG>
EventHandlerBase(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location, BACKLOG const& a_backlog)
:   m_eventType(a_eventType)
,   m_id(a_id)
,   m_type(a_type)
,   m_location(a_location)
,   m_backlog(a_backlog)
{

}

}   //namespace iot

#endif // IOT_EVENT_HANDLER_BASE_HXX