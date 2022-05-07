#ifndef IOT_PUB_SUB_HPP
#define IOT_PUB_SUB_HPP


#include <mutex>
#include "thread_job.hpp"
#include "iot_event_router.hpp"
#include "thread_group.hpp"
#include "blocking_queue.hpp"
#include "iot_pub_sub_internals.hpp"

namespace iot
{

class PubSub 
{
public:
    using Queue = mt::BlockingQueue<Event>;
    using FO = PubSubFO <EventRouter, Queue, Event>;   
    using Threads = mt::ThreadGroup<FO>;

    PubSub(EventRouter & a_router, Queue & a_queue, size_t a_concurrency = 1);
    ~PubSub();

    void stop();

private:
    size_t m_concurrency;
    FO m_fo;
    Threads m_threads;
};

}   //namspace iot

#endif //IOT_PUB_SUB_HPP