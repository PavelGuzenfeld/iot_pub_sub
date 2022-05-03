#ifndef IOT_TYPES_HPP
#define IOT_TYPES_HPP

#include <string>

namespace iot
{

using String = std::string;
using Location = std::string;
using Time = std::string;
using Config = std::string;
using log = std::string;

struct Event
{
    String m_eventType;
    Time m_eventTime;
    Location m_deviceLocation;
    String m_deviceID;
    String m_deviceType;
    String m_data;
    log m_loggers;
};

struct Attributes
{
    String m_eventType;
    String m_id;
    String m_type;
    Location m_location;
    log m_loggers;
};

}   //namespace iot

#endif  //IOT_TYPES_HPP