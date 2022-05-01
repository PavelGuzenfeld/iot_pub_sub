#include <string>
#include <time.h>
#include <iostream>

template<typename STRING, typename LOCATION, typename EVENT>
Device<STRING,LOCATION,EVENT>::Device(STRING const& a_id, STRING const& a_type, LOCATION const& a_location, STRING const& a_config)
: m_id(a_id)
, m_type(a_type)
, m_location(a_location)
, m_config(a_config)
{   

}

template<typename STRING, typename LOCATION, typename EVENT>
EVENT Device<STRING,LOCATION,EVENT>::publish()
{
    static unsigned int temp = 0;
    ++temp;
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    return EVENT{"temperature", std::string(asctime(curtime)), m_location, m_id, m_type, std::to_string(temp)};
}

template<typename STRING, typename LOCATION, typename EVENT>
void Device<STRING,LOCATION,EVENT>::subscribe(EVENT const& a_event)
{
    m_events.push_back(a_event);
    //std::cout << m_id << " " << m_type << " " << a_event.m_eventType << " " << a_event.m_eventTime << "\n";
}

template<typename STRING, typename LOCATION, typename EVENT>
std::vector<EVENT> const& Device<STRING,LOCATION,EVENT>::getEvents() const
{
    return m_events;
}

