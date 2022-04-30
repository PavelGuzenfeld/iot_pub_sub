#pragma once

#include <string>

namespace iot
{

struct DeviceConfig
{
    std::string m_id;
    std::string m_type;
    unsigned int m_room;
    unsigned int m_floor;
    std::string m_log;
    std::string m_config;
};

} // namespace iot
