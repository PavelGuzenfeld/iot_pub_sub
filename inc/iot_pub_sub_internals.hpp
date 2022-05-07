#ifndef IOT_PUB_SUB_INTERNALS_HPP
#define IOT_PUB_SUB_INTERNALS_HPP

#include <mutex>

namespace iot
{

template<typename ROUTER, typename QUEUE, typename EVENT> 
struct PubSubFO: public mt::ThreadJob
{
    PubSubFO(ROUTER& a_router, QUEUE& a_queue, bool a_on);
    void* operator()(void* a_arg) final;

    void stop();
    bool isON();

    ROUTER& m_router;
    QUEUE& m_queue;
    bool m_on;
    std::mutex m_mtx;
};

}   //namspace iot

#include "inl/iot_pub_sub_internals.hxx"

#endif //IOT_PUB_SUB_INTERNALS_HPP