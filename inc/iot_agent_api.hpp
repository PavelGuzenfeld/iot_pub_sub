#pragma once

#include "abstract.hpp"

namespace iot
{

template <typename EVENT>
struct EventProducer : public cpp::Abstract
{
    EventProducer() = default;
    virtual EVENT produceEvent() = 0;
};

template <typename EVENT>
struct EventHandler : public cpp::Abstract
{
    EventHandler() = default;
    virtual void storeEvent(EVENT const& a_event) = 0;
    virtual EVENT handleEvent() = 0;
};

}   //namespace iot