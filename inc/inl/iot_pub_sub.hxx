#ifndef IOT_PUB_SUB_HXX
#define IOT_PUB_SUB_HXX

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
PubSub<ROUTER, QUEUE,EVENT,THREADS>::PubSub(ROUTER const& a_router, QUEUE & a_queue, size_t a_concurrenty)
:   m_router(a_router)
,   m_queue(a_queue)
,   m_concurrency(a_concurrenty)
,   m_on(true)
,   m_fo{m_router,m_queue,m_on}
,   m_threads{m_fo, m_concurrency}
{

}

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
PubSub<ROUTER, QUEUE,EVENT,THREADS>::~PubSub()
{
    m_threads.join();
}

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
void PubSub<ROUTER, QUEUE,EVENT,THREADS>::run()
{
    m_on = true;
    while(m_on == true)
    {
        EVENT next;
        m_queue.dequeue(next);
        m_router.rout(next);
    }
}

template<typename ROUTER, typename QUEUE, typename EVENT, typename THREADS>
void PubSub<ROUTER, QUEUE,EVENT,THREADS>::stop()
{
    m_on = false;
}

template<typename ROUTER, typename QUEUE, typename EVENT>
PubSubFO<ROUTER, QUEUE, EVENT>::PubSubFO(ROUTER& a_router, QUEUE& a_queue, bool& a_on )
:   m_router(a_router)
,   m_queue(a_queue)
,   m_on(a_on)
{

}

template<typename ROUTER, typename QUEUE, typename EVENT> 
void* PubSubFO<ROUTER, QUEUE, EVENT>::operator()(void* a_arg)
{
    while(m_on == true)
    {
        EVENT next;
        m_queue.dequeue(next);
        m_router.rout(next);
    }
    return this;
}

#endif // IOT_PUB_SUB_HXX