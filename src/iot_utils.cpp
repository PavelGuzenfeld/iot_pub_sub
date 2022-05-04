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

}   //namespace iot
