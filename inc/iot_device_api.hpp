#pragma once

#include "abstract.hpp"

namespace iot
{

template <typename STRING>
struct Sensor : public cpp::Abstract
{
    Sensor() = default;
    virtual STRING eventData() = 0;
};

template <typename STRING>
struct Controller : public cpp::Abstract
{
    Controller() = default;
    virtual STRING handle(STRING const& a_eventData) = 0;
};

}   //namespace iot