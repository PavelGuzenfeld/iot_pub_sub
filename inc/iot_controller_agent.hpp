#ifndef IOT_CONTROLLER_AGENT
#define IOT_CONTROLLER_AGENT

#include "iot_event_handler_base.hpp"
#include "iot_controller_base.hpp"

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENET, typename BACKLOG, typename DEVICE>
class ControllerAgent :public iot::EventHandlerBase<STRING,LOCATION,EVENT,BACKLOG>, public iot::ControllerBase<STRING, DEVICE>
{
public:
    using EventBase = EventHandlerBase<STRING,LOCATION,EVENT,BACKLOG>;
    using Controller = iot::ControllerBase<STRING, DEVICE>;

    ControllerAgent(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location, BACKLOG const& a_backlog, DEVICE const& a_device);
    EVENT consumeEvent(EVENT const& a_event) final;
    EVENT handleEvent() final;

    bool isEmpty();

private:
    STRING handle(STRING const& a_eventData) final;
};

}   //namespace iot

#include "inl/iot_controller_agent.hxx"

#endif  //IOT_CONTROLLER_AGENT