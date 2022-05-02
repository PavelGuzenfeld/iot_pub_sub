#ifndef IOT_TEMPERATURE_SENSOR_HPP
#define IOT_TEMPERATURE_SENSOR_HPP

#include "iot_event_producer_base.hpp"
#include "iot_device_api.hpp"

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
class TemperatureSensor : public EventProducerBase<STRING,LOCATION,EVENT>, Sensor<STRING>
{
public:
    using EventBase = EventProducerBase<STRING,LOCATION,EVENT>;
    
    TemperatureSensor(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location);   

    EVENT produceEvent() final;
private:
    STRING eventData() final;
};

}   //namespace iot

#include "inl/iot_temperature_sensor.hxx"

#endif  //IOT_TEMPERATURE_SENSOR_HPP