#include <string>
#include <time.h>
#include <iostream>

template<typename STRING, typename LOCATION, typename EVENT>
Device<STRING,LOCATION,EVENT>::Device(STRING a_id, STRING a_type, LOCATION a_location, STRING a_config)
: m_id(a_id)
, m_type(a_type)
, m_location(a_location)
, m_config(a_config)
{

}

template<typename STRING, typename LOCATION, typename EVENT>
EVENT Device<STRING,LOCATION,EVENT>::publish()
{
    static unsigned int id = 0;
    ++id;
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    return EVENT{std::to_string(id), std::string(asctime(curtime)), std::to_string(m_location), std::to_string(m_id), std::to_string(m_type), "event data"};
}

template<typename STRING, typename LOCATION, typename EVENT>
void Device<STRING,LOCATION,EVENT>::Device::subscribe(EVENT const& a_event)
{
    std::cout << a_event.id << " " << a_event.m_eventTime << "\n";
}

