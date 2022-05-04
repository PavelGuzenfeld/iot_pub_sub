#include "iot_sensor.hpp"
#include "iot_utils.hpp"

namespace iot
{

Sensor::Sensor(Attributes const& a_att, Config const& a_conf)
:   m_attributes(a_att)
,   m_config(a_conf)
{

}

static String eventData(String const& a_conf)
{
    int from;
    nextNumber(a_conf, from);
    int to;
    nextNumber(a_conf, to);
    auto data = randomUniformDistribution(from, to);
    return std::to_string(data);
}

Event Sensor::produce()
{
    auto time = timestamp();
    auto data = eventData(m_config);
    return {
                m_attributes.m_eventType,
                
                m_attributes.m_id, 
                m_attributes.m_type, 

                m_attributes.m_location, 
                time, 
                
                data, 
                m_attributes.m_loggers
            };
}

} //namspace iot
