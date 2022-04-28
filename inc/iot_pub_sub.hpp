#ifndef IOT_PUB_SUB_HPP
#define IOT_PUB_SUB_HPP

#include<thread_job.hpp>

namespace iot
{

template<typename ROUTER, typename QUEUE, typename EVENT> 
struct PubSubFO: public mt::ThreadJob
{
    PubSubFO(ROUTER& a_router, QUEUE& a_queue, bool& a_on );
    void* operator()(void* a_arg) final;

    ROUTER& m_router;
    QUEUE& m_queue;
    bool& m_on;
};

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS> 
class PubSub 
{
public:
    using FO = PubSubFO <ROUTER,QUEUE,EVENT>;   

    PubSub(ROUTER const& a_router, QUEUE & a_queue, size_t a_concurrency = 1);
    ~PubSub();

    void run();
    void stop();

private:
    ROUTER m_router;
    QUEUE& m_queue;
    size_t m_concurrency;
    bool m_on;
    FO m_fo;
    THREADS m_threads;
};



#include "inl/iot_pub_sub.hxx"

}   //namspace iot

#endif //IOT_PUB_SUB_HPP