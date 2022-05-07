#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <chrono>

namespace mt
{

template<typename T>
BlockingQueue<T>::BlockingQueue()
 try
 :  m_mutex()
 ,  m_condVar()
 ,  m_queue()
 ,  m_shutdown()
 {

 }
catch(...)
{
    std::string msg = "Citor failed";
    throw BlockingQueueCtorFailed(msg);
}

template<typename T>
BlockingQueue<T>::~BlockingQueue()
{
    if(m_shutdown == false)
    {
        shutdown();
    }
}

template<typename T>
bool BlockingQueue<T>::enqueue(T const& a_element)
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {    
        m_queue.push(a_element);
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
bool BlockingQueue<T>::dequeue(T& a_retRef)
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.empty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        a_retRef = m_queue.back();
        m_queue.pop();
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
bool BlockingQueue<T>::dequeue()
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.empty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        m_queue.pop();
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
bool BlockingQueue<T>::dequeue(std::function<void(T const& a_retVal)> a_func)
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.empty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        auto retRef = m_queue.back();
        a_func(retRef);
        m_queue.pop();
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
bool BlockingQueue<T>::first(T& a_retRef) const
try
{
    std::unique_lock l(m_mutex);
    m_condVar.wait(l, [this]{return m_queue.empty() == false || m_shutdown == true;});
    if(m_shutdown == true)
    {
        return false;
    }
    else
    {
        a_retRef = m_queue.back();
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
size_t BlockingQueue<T>::size() const
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
bool BlockingQueue<T>::isEmpty() const
try
{
    std::unique_lock g(m_mutex);
    return m_queue.empty();
}
catch(...)
{
    std::string msg = "Internal component failed";
    throw BlockingQueueError(msg);
}

template<typename T>
void BlockingQueue<T>::shutdown()
{
    std::unique_lock g(m_mutex);
    m_shutdown = true;
    m_condVar.notify_all();
}

}   //namespace mt

#endif // BLOCKING_QUEUE_HXX