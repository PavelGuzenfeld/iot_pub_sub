#ifndef IOT_EVENT_ROUTER_HXX
#define IOT_EVENT_ROUTER_HXX

template<typename KEY, typename EVENT, typename DEVICE, typename CONTAINER>
iot::EventRouter<KEY,EVENT,DEVICE,CONTAINER>::EventRouter(CONTAINER && a_subs)
:   m_subs(a_subs)
{

}

template<typename KEY, typename EVENT, typename DEVICE, typename CONTAINER>
void iot::EventRouter<KEY,EVENT,DEVICE,CONTAINER>::rout(EVENT const& a_event) const
{
    auto subscribed = m_subs.find(a_event.m_eventType);
    if(subscribed == m_subs.end())
    {
        return;
    }

    auto const& devices = subscribed->second;
    for(auto d: devices)
    {
        d.subscribe(a_event);
    }
}

#endif // IOT_EVENT_ROUTER_HXX