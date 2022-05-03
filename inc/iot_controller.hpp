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
    using Device = std::unique_ptr<Device>;

    Controller(Attributes const& a_attributes, Device const& a_device, Config const& a_config);
    Event store(Event const& a_event) final;
    Event handle() final;
    Event probe();

private:
    Attributes m_attributes;
    Backlog m_eventBacklog;
    Device m_device;
};

 //m_device{std::make_unique<DEVICE>{a_config}}

}   //namespace iot

#endif  //IOT_CONTROLLER_HPP