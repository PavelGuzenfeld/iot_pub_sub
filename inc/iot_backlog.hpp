#ifndef IOT_BACKLOG_HPP
#define IOT_BACKLOG_HPP

#include "abstract.hpp"

namespace iot
{

template<typename EVENT>
struct BacklogProducer : cpp::Abstract
{
    BacklogProducer() = default;
    virtual bool add(EVENT const& a_event) = 0;
    virtual bool isFull() = 0;
};

template<typename EVENT>
struct BacklogConsumer : cpp::Abstract
{
    BacklogConsumer() = default;
    virtual bool remove(EVENT& a_event) = 0;
    virtual bool isEmpty() = 0;
};

}   // namespace iot

#endif //IOT_BACKLOG_HPP