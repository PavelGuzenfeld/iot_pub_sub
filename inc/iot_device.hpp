#pragma once

#include "iot_event.hpp"
#include <vector>

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename HANDLER>
class Device
{
public:
    Device(STRING const& a_id, STRING const& a_type, LOCATION const& a_location, STRING const& a_config, BACKLOG const& a_backlog, HANDLER const& handler);

    EVENT produce(STRING const& a_eventType, STRING const& a_data);
    void consume(EVENT const& a_event);
    void handle();

private:
    STRING m_id;
    STRING m_type;
    LOCATION m_location;
    BACKLOG m_events;
    HANDLER m_handler;
};

} // namespace iot

#include "inl/iot_device.hxx"
