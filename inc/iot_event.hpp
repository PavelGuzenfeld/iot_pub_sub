#ifndef IOT_EVENT_HPP
#define IOT_EVENT_HPP

namespace iot
{

template<typename STRING,typename TIME, typename LOCATION>
struct Event
{
    STRING m_eventType;
    TIME m_eventTime;
    LOCATION m_deviceLocation;
    STRING m_deviceID;
    STRING m_deviceType;
    STRING m_data;
};

}   //namespace iot

#endif // IOT_EVENT_HPP