#ifndef IOT_CONTROLLER_AGENT_HXX
#define IOT_CONTROLLER_AGENT_HXX

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENET, typename BACKLOG, typename DEVICE>
ControllerAgent<STRING,LOCATION,EVENET,BACKLOG,DEVICE>::ControllerAgent(STRING const& a_eventType, STRING const& a_id, STRING const& a_type, LOCATION const& a_location, BACKLOG const& a_backlog, DEVICE const& a_device)
:   EventBase(a_eventType, a_id, a_type, a_location, a_backlog)
,   Controller(a_device)
{

}

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename DEVICE>
EVENT ControllerAgent<STRING,LOCATION,EVENT,BACKLOG,DEVICE>::consumeEvent(EVENT const& a_event)
{
    return EventBase::m_backlog.add(a_event);
}

template<typename STRING, typename LOCATION, typename EVENET, typename BACKLOG, typename DEVICE>
EVENT ControllerAgent<STRING,LOCATION,EVENT,BACKLOG,DEVICE>::handleEvent()
{
    auto rout = [this](auto const& a_event) { handle(a_event.m_data);};
    return = EventBase::m_blocking.remove();
}

template<typename STRING, typename LOCATION, typename EVENT, typename BACKLOG, typename DEVICE>
STRING handle(STRING const& a_eventData)
{
    Controller.handle(a_eventData);
}

}   //namespace iot

#endif //IOT_CONTROLLER_AGENT_HXX