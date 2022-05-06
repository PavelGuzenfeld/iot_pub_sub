#include "iot_backlog.hpp"

namespace iot
{

bool Backlog::add(Event const& a_event)
{
    auto g = std::lock_guard(m_mtx);
    m_queue.push(a_event);
    return true;
}

bool Backlog::remove(Event& a_event)
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

bool Backlog::remove(std::function<void(Event const& a_retVal)> a_func)
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

bool Backlog::isEmpty()
{
    auto g = std::lock_guard(m_mtx);
    return m_queue.empty();
}

}   // namespace iot
