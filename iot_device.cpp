#pragma once

#include <queue>


namespace iot
{

Device::Device(std::string a_id, std::string a_type, Location a_location, std::string a_config)
: m_id(a_id)
, m_type(a_type)
, m_location(a_location)
, m_config(a_config)
{

}

void publish(Buffer a_msg, EventsQueue a_queueOfPubEvents)
{

}

} // namespace iot
