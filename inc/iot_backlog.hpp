#ifndef IOT_BACKLOG_HPP
#define IOT_BACKLOG_HPP

#include <functional>
#include <queue>
#include <mutex>
#include "abstract.hpp"

namespace iot
{

template<typename EVENT>
struct BacklogProducer : cpp::Abstract
{
    BacklogProducer() = default;
    virtual bool add(EVENT const& a_event) = 0;
};

template<typename EVENT>
struct BacklogConsumer : cpp::Abstract
{
    BacklogConsumer() = default;
    virtual bool remove(EVENT& a_event) = 0;
    virtual bool remove(std::function<void(EVENT const& a_retVal)> a_func) = 0;
};

template<typename EVENT>
class BacklogQueue : public BacklogProducer<EVENT>, public BacklogConsumer<EVENT>
{
public:
    BacklogQueue() = default;

    bool add(EVENT const& a_event)
    {
        auto g = std::lock_guard(m_mtx);
        m_queue.push(a_event);
        return true;
    }

    bool remove(EVENT& a_event)
    {
        auto g = std::lock_guard(m_mtx);
        if(m_queue.empty() == true)
        {
            return false;
        }
        a_event = m_queue.front();
        m_queue.pop();
        return true;
    }

    virtual bool remove(std::function<void(EVENT const& a_retVal)> a_func)
    {
        auto g = std::lock_guard(m_mtx);
        if(m_queue.empty() == true)
        {
            return false;
        }
        auto const& e = m_queue.front();
        a_func(e);
        m_queue.pop();
        return true;
    }

    bool isEmpty()
    {
        auto g = std::lock_guard(m_mtx);
        return m_queue.empty();
    }

private:
    std::queue<EVENT> m_queue;
    std::mutex m_mtx;
};

}   // namespace iot

#endif //IOT_BACKLOG_HPP