#ifndef IOT_PUB_SUB_INTERNALS_HXX
#define IOT_PUB_SUB_INTERNALS_HXX

namespace iot
{

template<typename ROUTER, typename QUEUE, typename EVENT>
PubSubFO<ROUTER, QUEUE, EVENT>::PubSubFO(ROUTER& a_router, QUEUE& a_queue, bool a_on )
:   m_router(a_router)
,   m_queue(a_queue)
,   m_on(a_on)
{

}

template<typename ROUTER, typename QUEUE, typename EVENT> 
void* PubSubFO<ROUTER, QUEUE, EVENT>::operator()(void* a_arg)
{
    while(isON() == true)
    {
        auto rout = [this](EVENT const& a_next) { m_router.rout(a_next);};
        m_queue.dequeue(rout);
    }
    return this;
}

template<typename ROUTER, typename QUEUE, typename EVENT>
void PubSubFO<ROUTER, QUEUE,EVENT>::stop()
{
    auto g = std::lock_guard(m_mtx);
    m_on = false;
}


template<typename ROUTER, typename QUEUE, typename EVENT>
bool PubSubFO<ROUTER, QUEUE,EVENT>::isON()
{
    auto g = std::lock_guard(m_mtx);
    return m_on;
}

}   //namespace iot

#endif // IOT_PUB_SUB_HXX