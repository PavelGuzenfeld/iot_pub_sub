#ifndef IOT_EVENT_ROUTER_HPP
#define IOT_EVENT_ROUTER_HPP

#include<map>
#include<vector>

namespace iot
{
 
template<typename KEY, typename EVENT, typename DEVICE, typename CONTAINER = std::map<KEY,std::vector<DEVICE>>>
class EventRouter
{
public:
    EventRouter(CONTAINER && a_subs);
    //TODO: EventRouter(CONTAINER const& a_subs);
    void rout(EVENT const& a_event) const;

private:
    CONTAINER m_subs; 
};

#include "inl/iot_event_router.hxx"

}   //namespace iot

#endif // IOT_EVENT_ROUTER_HPP