#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <functional>
#include <queue>
#include "blocking_queue_exception.hpp"

namespace mt
{

template<typename T>
// thread safe, NO RACE CONDITIONS
class BlockingQueue
{  
public:
    BlockingQueue();
    ~BlockingQueue();

    bool enqueue(T const& a_element);
    bool dequeue(T& a_retVal);
    bool dequeue(std::function<void(T const& a_retVal)> a_func);
    bool dequeue();
    bool first(T& a_status) const;

    size_t size() const;

    bool isEmpty() const;

    void shutdown();

private:
    BlockingQueue(BlockingQueue const& a_queue);
    BlockingQueue& operator=(BlockingQueue const& a_queue);

private:
   mutable std::mutex m_mutex;
   mutable std::condition_variable m_condVar;
   std::queue<T> m_queue;
   bool m_shutdown;
};

} //namespace mt

#include "inl/blocking_queue.hxx"

#endif // BLOCKING_QUEUE_HPP