#include <random>
#include <sstream>
#include <time.h>
#include "iot_utils.hpp"

namespace iot
{

Time timestamp()
{
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    return Time(asctime(curtime));
}

int randomUniformDistribution(int a_from, int a_to)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(a_from,a_to); // define the range

    return distr(gen);
}

bool nextNumber(String const& a_conf, int& a_retVal)
{
    std::stringstream ss;
    ss << a_conf;
    while (!ss.eof())
    {
        String temp;
        ss >> temp;
        a_retVal = 0;
        if (std::stringstream(temp) >> a_retVal)
        {
            return true;
        }
    }
    return false;
}

Event response(Attributes const& a_attributes, String a_data)
{
    return
    {
        a_attributes.m_eventType,

        a_attributes.m_id,
        a_attributes.m_type,

        a_attributes.m_location,
        timestamp(),

        a_data,
        a_attributes.m_loggers
    };
}

}   //namespace iot
