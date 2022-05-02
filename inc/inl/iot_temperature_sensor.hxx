#ifndef IOT_TEMPERATURE_SENSOR_HXX
#define IOT_TEMPERATURE_SENSOR_HXX

#include <random>
#include <time.h>

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
TemperatureSensor<STRING,LOCATION,EVENT>::TemperatureSensor(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location)
:   EventBase(a_eventType, a_id, a_type, a_location)
{

}

std::string timestamp()
{
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    auto strTime = std::string(asctime(curtime));
    strTime.pop_back();
    return strTime;
}

template<typename STRING, typename LOCATION, typename EVENT>
EVENT TemperatureSensor<STRING,LOCATION,EVENT>::produceEvent()
{
    auto time = timestamp();
    auto data = eventData();
    return EVENT{EventBase::m_eventType, time, EventBase::m_location, EventBase::m_id, EventBase::m_type, data};
}

template<typename STRING, typename LOCATION, typename EVENT>
STRING TemperatureSensor<STRING,LOCATION,EVENT>::eventData()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(25, 63); // define the range
    return std::to_string(distr(gen));
}

} //namspace iot

#endif  //IOT_TEMPERATURE_SENSOR_HXX