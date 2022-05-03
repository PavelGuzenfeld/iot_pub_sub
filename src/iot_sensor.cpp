#include <random>
#include <time.h>
#include <sstream>
#include "iot_sensor.hpp"

#include <iostream>

namespace iot
{

Sensor::Sensor(Attributes const& a_att, Config const& a_conf)
:   m_attributes(a_att)
,   m_config(a_conf)
{

}

static Time timestamp()
{
    time_t ptm = time(nullptr);
    struct tm* curtime = localtime ( &ptm );
    return Time(asctime(curtime));
}

static int getNextNumber(std::stringstream & a_str)
{
    int found = 0;
    while (!a_str.eof())
    {
        String temp;
        a_str >> temp;
        if (std::stringstream(temp) >> found)
        {
            return found;
        }
    }
    throw "bad config";
}

static int parse(String const& a_conf)
{
    std::stringstream ss;
    ss << a_conf;   
    return getNextNumber(ss);
}

static String eventData(String const& a_conf)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator

    int from = parse(a_conf);
    int to = parse(a_conf);
    std::uniform_int_distribution<> distr(from, to); // define the range

    return std::to_string(distr(gen));
}

Event Sensor::produce()
{
    auto time = timestamp();
    auto data = eventData(m_config);
    return {m_attributes.m_eventType, time, m_attributes.m_location, m_attributes.m_id, m_attributes.m_type, data, m_attributes.m_loggers};
}

} //namspace iot
