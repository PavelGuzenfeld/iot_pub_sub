#ifndef IOT_EVENT_ROUTER_HPP
#define IOT_EVENT_ROUTER_HPP

#include <map>
#include <vector>

namespace iot
{
 
template<typename KEY, typename EVENT, typename DEVICE, typename CONTAINER = std::map<KEY,std::vector<DEVICE>>>
class EventRouter
{
public:
    explicit EventRouter(CONTAINER && a_subs);
    explicit EventRouter(CONTAINER const& a_subs);
    ~EventRouter() = default;

    void rout(EVENT const& a_event);

private:
    CONTAINER m_subs;
};

#include "inl/iot_event_router.hxx"

}   //namespace iot

#endif // IOT_EVENT_ROUTER_HPP

//TODO: change container to better name
//TODO: change key to better name
//TODO: add default cctor and operator=()