#include <mu_test.h>
#include <string>
#include <chrono>
#include <thread>
#include "iot_event.hpp"
#include "iot_event_router.hpp"
#include "iot_device.hpp"
#include "iot_pub_sub.hpp"
#include "blocking_queue.hpp"
#include "thread_group.hpp"

BEGIN_TEST(router_creat)
{
    auto r = iot::EventRouter<int,int,int>{{{1, {11,111}}, {2,{22,222}}}};
    ASSERT_PASS();
}
END_TEST

BEGIN_TEST(creat_device)
{
    auto event = iot::Device<std::string, std::string, std::string>{"id - device1","type - heat"," location - floor 1", " no config"};
    ASSERT_PASS();
}
END_TEST

BEGIN_TEST(sensor_and_controller_in_router)
{
    using STRING = std::string;
    using EVENT = iot::Event<STRING,STRING,STRING>;
    using DEVICE = iot::Device<STRING, STRING, EVENT>;

    auto sensor = DEVICE{"id - temperature sensor 1","type - heat_sensor"," location - floor 1", "no config"};
    auto airCon1 = DEVICE{"id - air conditioner 1","type - air_con"," location - floor 1", "temp > 30"};
    auto airCon2 = DEVICE{"id - air conditioner 2","type - air_con"," location - floor 1", "temp > 30"};
 
    auto r = iot::EventRouter<STRING,EVENT,DEVICE>{{ {"temperature", {airCon1,airCon2}} }};

    for(size_t i = 0; i<5; ++i)
    {
        using namespace std::chrono_literals;
        auto event = sensor.publish();
        //std::this_thread::sleep_for(2000ms);
        r.rout(event);
        TRACER<< event.m_deviceID << " " <<event.m_eventType << "\n";
    }

    ASSERT_PASS();
}
END_TEST

BEGIN_TEST(pub_sub)
{
    using STRING = std::string;
    using EVENT = iot::Event<STRING,STRING,STRING>;
    using DEVICE = iot::Device<STRING, STRING, EVENT>;
    using ROUTER = iot::EventRouter<STRING,EVENT,DEVICE>;
    using QUEUE = mt::BlockingQueue<EVENT>;
    using FO = iot::PubSubFO<ROUTER,QUEUE,EVENT>;
    using PUBSUB = iot::PubSub<ROUTER,QUEUE,EVENT,mt::ThreadGroup<FO>>;

    auto sensor = DEVICE{"id - temperature sensor 1","type - heat_sensor"," location - floor 1", "no config"};
    auto airCon1 = DEVICE{"id - air conditioner 1","type - air_con"," location - floor 1", "temp > 30"};
    auto airCon2 = DEVICE{"id - air conditioner 2","type - air_con"," location - floor 1", "temp > 30"};
    auto eventTemperature = "temperature";
    
    auto router = ROUTER{{ {eventTemperature, {airCon1,airCon2}} }};
    auto q = QUEUE();
    auto pubSub = PUBSUB{router, q, 2};
    
    for(size_t i = 0; i<5; ++i)
    {
        using namespace std::chrono_literals;
        auto event = sensor.publish();
        //std::this_thread::sleep_for(2000ms);
        q.enqueue(event);
        TRACER<< event.m_deviceID << " " <<event.m_eventType << "\n";
    }
    pubSub.stop();
    ASSERT_PASS();

}
END_TEST

BEGIN_SUITE(IOT PROJECT)
    // TEST(router_creat)
    // TEST(creat_device)
    // TEST(sensor_and_controller_in_router)
    TEST(pub_sub)
END_SUITE