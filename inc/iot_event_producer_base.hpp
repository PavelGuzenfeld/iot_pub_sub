#ifndef IOT_EVENT_PRODUCER_BASE_HPP
#define IOT_EVENT_PRODUCER_BASE_HPP

#include "iot_agent_api.hpp"

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
class EventProducerBase : public EventProducer<EVENT>
{
protected:
    EventProducerBase(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location);

    virtual EVENT produceEvent() = 0;

protected:
    STRING m_eventType;
    STRING m_id;
    STRING m_type;
    LOCATION m_location;
};

}   //namsepace iot

#include "inl/iot_event_producer_base.hxx"

#endif  //IOT_EVENT_PRODUCER_BASE_HPP