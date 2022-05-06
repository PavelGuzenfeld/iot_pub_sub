#ifndef IOT_BACKLOG_HPP
#define IOT_BACKLOG_HPP

#include <queue>
#include <mutex>
#include "iot_backlog_api.hpp"

namespace iot
{

class Backlog : public BacklogProducer, public BacklogConsumer
{
public:
    Backlog() = default;

    bool add(Event const& a_event);
    bool remove(Event& a_event);
    bool remove(std::function<void(Event const& a_retVal)> a_func);

    bool isEmpty();

private:
    std::queue<Event> m_queue;
    std::mutex m_mtx;
};

}   // namespace iot

#endif //IOT_BACKLOG_HPP