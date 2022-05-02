#ifndef IOT_EVENT_PRODUCER_BASE_HXX
#define IOT_EVENT_PRODUCER_BASE_HXX

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
EventProducerBase<STRING,LOCATION,EVENT>::EventProducerBase(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location)
:   m_eventType(a_eventType)
,   m_id(a_id)
,   m_type(a_type)
,   m_location(a_location)
{

}

}   //namespace iot

#endif //IOT_EVENT_PRODUCER_BASE_HXX