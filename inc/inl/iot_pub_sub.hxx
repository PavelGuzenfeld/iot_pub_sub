#ifndef IOT_PUB_SUB_HXX
#define IOT_PUB_SUB_HXX

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
PubSub<ROUTER, QUEUE,EVENT,THREADS>::PubSub(ROUTER & a_router, QUEUE & a_queue, size_t a_concurrenty)
:   m_concurrency(a_concurrenty)
,   m_fo{a_router,a_queue,true}
,   m_threads{m_fo, m_concurrency}
{

}

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
PubSub<ROUTER, QUEUE,EVENT,THREADS>::~PubSub()
{
    m_threads.join();
}

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
void PubSub<ROUTER, QUEUE,EVENT,THREADS>::stop()
{
    m_fo.m_queue.shutdown();
    m_fo.stop();
}



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
        // EVENT next;
        // m_queue.dequeue(next);
        // m_router.rout(next);
        auto rout = [this](EVENT const& next) { m_router.rout(next);};
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

#endif // IOT_PUB_SUB_HXX