#ifndef IOT_SENSOR_BASE
#define IOT_SENSOR_BASE

#include "iot_device_api.hpp"

namespace iot
{

template<typename STRING>
struct SensorBase : Sensor<STRING>
{
    SensorBase(STRING const& a_config);
    virtual STRING eventData() = 0;

    STRING()

};

}   //namespace iot

#endif // IOT_SENSOR_BASE