#ifndef IOT_MANAGER_HPP
#define IOT_MANAGER_HPP

#include <string>
#include "iot_event.hpp"
#include "iot_event_router.hpp"
#include "iot_device.hpp"
#include "iot_pub_sub.hpp"
#include "blocking_queue.hpp"
#include "thread_group.hpp"

namespace iot
{

class Manager
{
public:
    using STRING = std::string;
    using EVENT = iot::Event<STRING,STRING,STRING>;
    using DEVICE = iot::Device<STRING, STRING, EVENT>;
    using ROUTER = iot::EventRouter<STRING,EVENT,DEVICE>;
    using QUEUE = mt::BlockingQueue<EVENT>;
    using FO = iot::PubSubFO<ROUTER,QUEUE,EVENT>;
    using PUBSUB = iot::PubSub<ROUTER,QUEUE,EVENT,mt::ThreadGroup<FO>>;


private:
    QUEUE m_queue;
    ROUTER m_router;
    PUBSUB m_pubSub;
};

}   //namespace iot

#endif //IOT_MANAGER_HPP