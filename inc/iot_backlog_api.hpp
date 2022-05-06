#ifndef BACKLOG_IOT_API
#define BACKLOG_IOT_API

#include <functional>
#include "abstract.hpp"
#include "iot_types.hpp"

namespace iot
{

struct BacklogProducer : cpp::Abstract
{
    BacklogProducer() = default;
    virtual bool add(Event const& a_event) = 0;
};

struct BacklogConsumer : cpp::Abstract
{
    BacklogConsumer() = default;
    virtual bool remove(Event& a_event) = 0;
    virtual bool remove(std::function<void(Event const& a_retVal)> a_func) = 0;
};

}   //namspace iot

#endif  //BACKLOG_IOT_API