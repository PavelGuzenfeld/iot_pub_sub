#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <chrono>

template<typename T>
 mt::BlockingQueue<T>::BlockingQueue(size_t a_size)
 try
 :  m_mutex()
 ,  m_condVar()
 ,  m_queue(a_size)
 ,  m_shutdown()
 {

 }
catch(...)
{
    std::string msg = "Citor failed";
    throw BlockingQueueCtorFailed(msg);
}

template<typename T>
mt::BlockingQueue<T>::~BlockingQueue()
{
    if(m_shutdown == false)
    {
        shutdown();
    }
}

template<typename T>
bool mt::BlockingQueue<T>::enqueue(T const& a_element)
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.isFull() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {    
        m_queue.enqueue(a_element);
        m_condVar.notify_all();
    }
    return true;
}
catch(...)
{
    std::string msg = "Enqueue failed";
    throw BlockingQueueEnqueueFailed(msg);
}

template<typename T>
bool mt::BlockingQueue<T>::dequeue(T& a_retRef)
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.isEmpty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        a_retRef = m_queue.first();
        m_queue.dequeue();
        m_condVar.notify_all();
    }
    return true;
}
catch(...)
{
    std::string msg = "Dequeue failed";
    throw BlockingQueueDequeueFailed(msg); 
}

template<typename T>
bool mt::BlockingQueue<T>::dequeue()
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.isEmpty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        m_queue.dequeue();
        m_condVar.notify_all();
    }
    return true;
}
catch(...)
{
    std::string msg = "Dequeue failed";
    throw BlockingQueueDequeueFailed(msg);
}

template<typename T>
bool mt::BlockingQueue<T>::first(T& a_retRef) const
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.isEmpty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        a_retRef = m_queue.first();
        m_condVar.notify_all();
    }
    return true;
}
catch(...)
{
    std::string msg = "First failed";
    throw BlockingQueueDequeueFailed(msg);
}

template<typename T>
size_t mt::BlockingQueue<T>::size() const
try
{
    std::unique_lock g(m_mutex);
    return m_queue.size();
}
catch(...)
{
    std::string msg = "Internal component failed";
    throw BlockingQueueError(msg);
}

template<typename T>
bool mt::BlockingQueue<T>::isEmpty() const
try
{
    std::unique_lock g(m_mutex);
    return m_queue.isEmpty();
}
catch(...)
{
    std::string msg = "Internal component failed";
    throw BlockingQueueError(msg);
}

template<typename T>
bool mt::BlockingQueue<T>::isFull() const
try
{
    std::unique_lock g(m_mutex);
    return m_queue.isFull();
}
catch(...)
{
    std::string msg = "Internal component failed";
    throw BlockingQueueError(msg);
}

template<typename T>
void mt::BlockingQueue<T>::shutdown()
{
    std::unique_lock g(m_mutex);
    m_shutdown = true;
    m_condVar.notify_all();
}

#endif // BLOCKING_QUEUE_HXX