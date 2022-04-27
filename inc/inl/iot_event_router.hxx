#ifndef IOT_EVENT_ROUTER_HXX
#define IOT_EVENT_ROUTER_HXX

template<typename EVENT, typename DEVICE, typename CONTAINER>
iot::EventRouter<EVENT,DEVICE,CONTAINER>::EventRouter(CONTAINER && a_subs)
:   m_subs(a_subs)
{

}

template<typename EVENT, typename DEVICE, typename CONTAINER>
void iot::EventRouter<EVENT,DEVICE,CONTAINER>::rout(EVENT const& a_event)
{
    auto subscribed = m_subs.find(a_event);
    if(subscribed = m_subs.end())
    {
        return;
    }

    for(auto s: subscribed.second)
    {
        s.subscribe(a_event);
    }
}

#endif // IOT_EVENT_ROUTER_HXX