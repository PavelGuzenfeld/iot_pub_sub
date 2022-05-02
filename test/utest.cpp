#include <mu_test.h>
#include <string>
#include <chrono>
#include <thread>
#include "iot_event.hpp"
#include "iot_event_router.hpp"
#include "iot_device.hpp"
#include "iot_pub_sub.hpp"
#include "iot_agent_factory.hpp"
#include "iot_ini_reader.hpp"
#include "blocking_queue.hpp"
#include "thread_group.hpp"

BEGIN_TEST(router_creat)
{
    auto r = iot::EventRouter<int,int,int>{{{1, {11,111}}, {2,{22,222}}}};
    ASSERT_PASS();
}
END_TEST

BEGIN_TEST(device_creat)
{
    auto device = iot::Device<std::string, std::string, std::string>{"id - device1","type - heat"," location - floor 1", " no config"};    
    ASSERT_PASS();
}
END_TEST

// BEGIN_TEST(router_inner_logic)
// {
//     using String = std::string;
//     using Event = iot::Event<STRING,STRING,STRING>;
//     using Device = iot::Device<STRING, STRING, EVENT>;

//     auto sensor = Device{"temperature sensor 1","heat_sensor","floor 1", "no config"};
//     auto airCon1 = Device{"con 1","air_con","floor 1", "temp > 30"};
//     auto airCon2 = Device{"con 2","air_con","floor 1", "temp > 30"};
// }
// END_TEST

BEGIN_TEST(send_events_to_router)
{
    using STRING = std::string;
    using EVENT = iot::Event<STRING,STRING,STRING>;
    using Device = iot::Device<STRING, STRING, EVENT>;

    auto sensor = Device{"temperature sensor 1","heat_sensor","floor 1", "no config"};
    auto airCon1 = Device{"con 1","air_con","floor 1", "temp > 30"};
    auto airCon2 = Device{"con 2","air_con","floor 1", "temp > 30"};
    
    auto router = iot::EventRouter<STRING,EVENT,Device>{{ {"temperature", {airCon1,airCon2}} }};

    for(size_t i = 0; i < 5; ++i)
    {
        auto event = sensor.produce("temperature", std::to_string(i));
        TRACER<< "Device id - " << event.m_deviceID << "| event: " << event.m_eventType << "\n";
        router.rout(event);
    }

    auto const& e1 = airCon2.getEvents();
    auto count = e1.size();

    ASSERT_EQUAL(count, 5);
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
    
    for(size_t i = 0; i < 5; ++i)
    {
        auto event = sensor.produce("temperature", std::to_string(i));
        q.enqueue(event);
        TRACER<< event.m_deviceID << " " <<event.m_eventType << "\n";
    }
    pubSub.stop();

    auto const& e1 = airCon1.getEvents();
    auto count = e1.size();

    ASSERT_EQUAL(count, 5);

    ASSERT_PASS();

}
END_TEST

BEGIN_TEST(so)
    using String = std::string;
    using Event = iot::Event<String,String,String>;
    using Device = iot::Device<String, String, Event>;
    using Agent = iot::AgentFactory<Device, ConfigFile>;

    
END_TEST


BEGIN_SUITE(IOT PROJECT)
    TEST(router_creat)
    TEST(device_creat)
    TEST(send_events_to_router)
    TEST(pub_sub)
    TEST(so)
END_SUITE