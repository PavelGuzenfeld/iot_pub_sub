#ifndef IOT_UTILS_HPP
#define IOT_UTILS_HPP

#include "iot_types.hpp"

namespace iot
{

    Time timestamp();
    int randomUniformDistribution(int a_from, int a_to);
    bool nextNumber(String const& a_conf, int& a_retVal);

}   //namespace iot

#endif  //IOT_UTILS_HPP