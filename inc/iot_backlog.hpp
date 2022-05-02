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
    virtual bool isFull();
};

template<typename EVENT>
struct BacklogConsumer : cpp::Abstract
{
    BacklogConsumer() = default;
    virtual bool remove(EVENT& a_event) = 0;
    virturl bool isEmpty();
};

}   // namespace iot

#endif //IOT_BACKLOG_HPP