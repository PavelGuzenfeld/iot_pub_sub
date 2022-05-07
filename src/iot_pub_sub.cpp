#include "iot_pub_sub.hpp"

namespace iot
{

PubSub::PubSub(EventRouter & a_router, Queue & a_queue, size_t a_concurrency)
:   m_concurrency(a_concurrency)
,   m_fo{a_router,a_queue,true}
,   m_threads{m_fo, m_concurrency}
{

}

PubSub::~PubSub()
{
    m_threads.join();
}

void PubSub::stop()
{
    m_fo.m_queue.shutdown();
    m_fo.stop();
}

}//namespace iot