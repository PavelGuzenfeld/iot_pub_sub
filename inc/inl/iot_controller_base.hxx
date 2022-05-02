#ifndef IOT_CONTROLLER_BASE_HXX
#define IOT_CONTROLLER_BASE_HXX

namespace iot
{

template<typename STRING, typename DEVICE>
ControllerBase<STRING,DEVICE>::ControllerBase(STRING const& a_config)
:   m_device{std::make_unique<DEVICE>{a_config}}
{

}

}   //namespace iot


#endif //IOT_CONTROLLER_BASE_HXX