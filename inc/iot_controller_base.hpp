#ifndef IOT_CONTROLLER_BASE_HPP
#define IOT_CONTROLLER_BASE_HPP

#include<memory>

namespace iot
{

template<typename STRING, typename DEVICE>
class ControllerBase : public Controller<STRING>
{
protected:
    explicit ControllerBase(STRING const& a_config)
    virtual STRING handle(STRING const& a_eventData) = 0;

    std::unique_ptr<DEVICE> m_device;
};

}   //namespace iot

#include "inl/iot_controller_base.hpp"

#endif //IOT_CONTROLLER_BASE_HPP