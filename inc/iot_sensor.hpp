#ifndef IOT_SENSOR_HPP
#define IOT_SENSOR_HPP

#include "iot_agent_api.hpp"
#include "iot_device_api.hpp"

namespace iot
{

class Sensor : public EventProducer
{
public:  
    Sensor(Attributes const& a_attributes, Config const& a_conf);   

    Event produce() final;

private:
    Attributes m_attributes;
    Config m_config;
};

}   //namespace iot

#endif  //IOT_SENSOR_HPP