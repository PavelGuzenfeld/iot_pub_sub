#ifndef IOT_EVENT_ROUTER_HPP
#define IOT_EVENT_ROUTER_HPP

#include<map>
#include<vector>

namespace iot
{
 
template<typename EVENT, typename DEVICE, typename CONTAINER = std::map<EVENT,std::vector<DEVICE>>>
class EventRouter
{
public:
    EventRouter(CONTAINER && a_subs);
    void rout(EVENT const& a_event);

private:
    CONTAINER m_subs; 

};

#include "inl/iot_event_router.hxx"

}   //namespace iot

#endif // IOT_EVENT_ROUTER_HPP