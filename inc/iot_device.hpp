#pragma once

#include "iot_event.hpp"
#include <vector>

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
class Device
{
public:
    Device(STRING const& a_id, STRING const& a_type, LOCATION const& a_location, STRING const& a_config);

    EVENT publish();
    void subscribe(EVENT const& a_event);

    std::vector<EVENT> const& getEvents() const;
private:
    std::vector<EVENT> m_events;

private:
    STRING m_id;
    STRING m_type;
    LOCATION m_location;
    STRING m_config;
};

#include "inl/iot_device.hxx"

} // namespace iot
