#include <string>
#include <time.h>
#include <iostream>
#include <iot_backlog.hpp>

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename HANDLER>
Device<STRING, LOCATION, EVENT, BACKLOG, HANDLER>::Device(STRING const& a_id, STRING const& a_type, LOCATION const& a_location, STRING const& a_config, BACKLOG const& a_backlog, HANDLER const& handler)
: m_id(a_id)
, m_type(a_type)
, m_location(a_location)
, m_events(a_backlog)
, m_handler(a_config, m_events)
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

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename HANDLER>
EVENT Device<STRING, LOCATION, EVENT, BACKLOG, HANDLER>::produce(STRING const& a_eventType, STRING const& a_data)
{
    auto time = timestamp();
    return EVENT{a_eventType, time, m_location, m_id, m_type, a_data};
}

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename HANDLER>
void Device<STRING, LOCATION, EVENT, BACKLOG, HANDLER>::consume (EVENT const& a_event)
{
    m_events.add(a_event);
    std::cout << m_id << " | " << a_event.m_eventType << " | " << a_event.m_eventTime <<" "<< a_event.m_data <<" "<< "\n";
    std::cout << "number of events "<< m_events.size() << "\n";
}

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename HANDLER>
void Device<STRING, LOCATION, EVENT, BACKLOG, HANDLER>::handle ()
{
    m_handler.handle();
}

}   //namspace iot