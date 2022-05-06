#ifndef IOT_EVENT_ROUTER_HPP
#define IOT_EVENT_ROUTER_HPP

#include <map>
#include <vector>
#include "iot_controller.hpp"

namespace iot
{
 
class EventRouter
{
public:
    using Subscriptions = std::map<String,std::vector<Controller>>;

    explicit EventRouter(Subscriptions& a_subs);
    ~EventRouter() = default;

    void rout(Event const& a_event);

private:
    Subscriptions m_subs;
};

}   //namespace iot

#endif // IOT_EVENT_ROUTER_HPP
