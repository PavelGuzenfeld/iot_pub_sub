#ifndef IOT_CONTROLLER_HPP
#define IOT_CONTROLLER_HPP

#include <memory>
#include "iot_agent_api.hpp"
#include "iot_device_api.hpp"
#include "iot_backlog.hpp"

namespace iot
{

class Controller : public EventHandler
{
public:
    using DevicePtr = std::shared_ptr<Device>;
    Controller(Attributes const& a_attributes, DevicePtr a_device);
    Event store(Event const& a_event) final;
    Event handle() final;
    Event probe();

private:
    Attributes m_attributes;
    Backlog m_eventBacklog;
    DevicePtr m_device;
};

}   //namespace iot

#endif  //IOT_CONTROLLER_HPP