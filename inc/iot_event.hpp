#ifndef IOT_EVENT_HPP
#define IOT_EVENT_HPP

namespace iot
{

template<typename STRING,typename TIME, typename LOCATION>
struct Event
{
    STRING m_eventId;
    TIME m_eventTime;
    LOCATION m_deviceLocation;
    STRING m_deviceID;
    STRING m_deviceType;
    STRING m_data;

    constexpr bool operator()( const Event& a_lhs, const Event& a_rhs ) const;
};

#include "inl/iot_event.hxx"

}   //namespace iot

#endif // IOT_EVENT_HPP