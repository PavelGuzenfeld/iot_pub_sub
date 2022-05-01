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

std::string timestamp()
{
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    auto strTime = std::string(asctime(curtime));
    strTime.pop_back();
    return strTime;
}

template<typename STRING, typename LOCATION, typename EVENT>
EVENT Device<STRING,LOCATION,EVENT>::produce(STRING const& a_eventType, STRING const& a_data)
{
    auto time = timestamp();
    return EVENT{a_eventType, time, m_location, m_id, m_type, a_data};
}

template<typename STRING, typename LOCATION, typename EVENT>
void Device<STRING,LOCATION,EVENT>::consume (EVENT const& a_event)
{
    m_events.push_back(a_event);
    std::cout << m_id << " | " << a_event.m_eventType << " | " << a_event.m_eventTime <<" "<< a_event.m_data <<" "<< "\n";
    std::cout << "number of events "<< m_events.size() << "\n";
}

template<typename STRING, typename LOCATION, typename EVENT>
std::vector<EVENT> const& Device<STRING,LOCATION,EVENT>::getEvents() const
{
    std::cout << "returning number of events "<< m_events.size() << "\n";
    return m_events;
}

