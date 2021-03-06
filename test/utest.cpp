#include "mu_test.h"
#include <vector>
#include "iot_sensor.hpp"
#include "iot_backlog.hpp"
#include "iot_controller.hpp"
#include "iot_air_con.hpp"
#include "iot_event_router.hpp"
#include "iot_pub_sub.hpp"

BEGIN_TEST(temperature_sensor)
{
    auto sensor  = iot::Sensor{{"temperature", "T-1", "Thermometer", "second floor","logger - 1"}, {"26 - 65"}};
    auto event = sensor.produce();
    
    TRACER << "time - " << event.m_eventTime << " | data: " << event.m_data << "\n"; 
    ASSERT_EQUAL_STR(event.m_eventType.c_str(), "temperature");
    ASSERT_EQUAL_STR(event.m_deviceID.c_str(), "T-1");
    ASSERT_EQUAL_STR(event.m_deviceType.c_str(), "Thermometer");
    ASSERT_EQUAL_STR(event.m_deviceLocation.c_str(), "second floor");
}
END_TEST

BEGIN_TEST(backlog)
{
    auto backlog = iot::Backlog();
    auto vec =  std::vector<iot::Event>{{"1"},{"2"},{"3"}};

    for(auto e: vec)
    {
        backlog.add(e);
    }
    auto i = 0;
    while(backlog.isEmpty() == false)
    {
        iot::Event e;
        backlog.remove(e);
        ASSERT_EQUAL(e.m_eventType, vec[i].m_eventType);
        TRACER << e.m_eventType << "\n";
        ++i;
    }
    ASSERT_EQUAL(backlog.isEmpty(), true);

    for(auto e: vec)
    {
        backlog.add(e);
    }
    
    auto mutatedBacklog = iot::Backlog();
    while(backlog.isEmpty() == false)
    {
        iot::String e = {};
        auto echo = [&](iot::Event const& a_event){e = "echo " + a_event.m_eventType;};
        backlog.remove(echo);
        mutatedBacklog.add({e});
    }

    i = 0;
    while(mutatedBacklog.isEmpty() == false)
    {
        iot::Event e;
        mutatedBacklog.remove(e);
        ASSERT_EQUAL(e.m_eventType, iot::String("echo ") + vec[i].m_eventType);
        TRACER << e.m_eventType << "\n";
        ++i;
    }
}
END_TEST

BEGIN_TEST(controller_agent)
{
    auto sensor  = iot::Sensor{{"temperature", "T-1", "Thermometer", "second floor","logger - 1"}, {"26 - 65"}};
    auto event = sensor.produce();
    auto airCon = std::make_shared<iot::AirCon>("Air con config");
    auto controller = iot::Controller({"temperature", "Air-1", "air_con", "second floor","logger - 1"}, {airCon});
    
    auto response = controller.store(event);
    TRACER << response.m_data << " " << response.m_eventType << " by " << response.m_deviceID << "\n";
    ASSERT_EQUAL(response.m_eventType, "temperature");
    ASSERT_EQUAL(response.m_deviceID, "Air-1");
    ASSERT_EQUAL(response.m_data, "stored");

    response = controller.handle();
    TRACER << response.m_data << " " << response.m_eventType << " by " << response.m_deviceID << "\n";
    ASSERT_EQUAL(response.m_eventType, "temperature");
    ASSERT_EQUAL(response.m_deviceID, "Air-1");
    ASSERT_EQUAL(response.m_data.substr(0, response.m_data.find(" ")), "handled");

    response = controller.probe();
    TRACER << response.m_data << " " << response.m_eventType << " by " << response.m_deviceID << "\n";
    ASSERT_EQUAL(response.m_eventType, "temperature");
    ASSERT_EQUAL(response.m_deviceID, "Air-1");
    ASSERT_EQUAL(response.m_data, "probed");
}
END_TEST

BEGIN_TEST(send_events_to_router)
{
    auto airCon = std::make_shared<iot::AirCon>("Air con config");
    auto controller = iot::Controller({"temperature", "Air-1", "air_con", "second floor","logger - 1"}, {airCon});

    auto eventSubscribers = iot::EventRouter::Subscriptions{};
    eventSubscribers["temperature"].emplace_back(iot::Controller{{"temperature", "Air-1", "air_con", "second floor","logger - 1"},{airCon}});
    eventSubscribers["temperature"].emplace_back(iot::Controller{{"temperature", "Air-2", "air_con", "second floor","logger - 1"},{airCon}});    
    auto router = iot::EventRouter{eventSubscribers};

    
    auto sensor = iot::Sensor{{"temperature", "T-1", "Thermometer", "second floor","logger - 1"}, {"26 - 65"}};
    for(size_t i = 0; i < 5; ++i)
    {
        auto event = sensor.produce();
        TRACER<< "Device id - " << event.m_deviceID << "| event: " << event.m_eventType << "\n";
        router.rout(event);
    }

    auto& subscribers = eventSubscribers["temperature"];
    auto count = 0;
    while(subscribers[0].handle().m_deviceType != "")
    {
        ++count;
    }
    ASSERT_EQUAL(count, 5);

    count = 0;    
    while(subscribers[1].handle().m_deviceType != "")
    {
        ++count;
    }
    ASSERT_EQUAL(count, 5);
}
END_TEST

// BEGIN_TEST(blocking_q)
// {
//     auto q = mt::BlockingQueue<iot::Event>();
//     q.enqueue({});
//     q.dequeue();
//     q.size();
//     q.isEmpty();
//     ASSERT_PASS();
// }
// END_TEST

// BEGIN_TEST(pub_sub)
// {
//     using STRING = std::string;
//     using EVENT = iot::Event<STRING,STRING,STRING>;
//     using DEVICE = iot::Device<STRING, STRING, EVENT>;
//     using ROUTER = iot::EventRouter<STRING,EVENT,DEVICE>;
//     using QUEUE = mt::BlockingQueue<EVENT>;
//     using FO = iot::PubSubFO<ROUTER,QUEUE,EVENT>;
//     using PUBSUB = iot::PubSub<ROUTER,QUEUE,EVENT,mt::ThreadGroup<FO>>;

//     auto sensor = DEVICE{"id - temperature sensor 1","type - heat_sensor"," location - floor 1", "no config"};
//     auto airCon1 = DEVICE{"id - air conditioner 1","type - air_con"," location - floor 1", "temp > 30"};
//     auto airCon2 = DEVICE{"id - air conditioner 2","type - air_con"," location - floor 1", "temp > 30"};
//     auto eventTemperature = "temperature";
    
//     auto router = ROUTER{{ {eventTemperature, {airCon1,airCon2}} }};
//     auto q = QUEUE();
//     auto pubSub = PUBSUB{router, q, 2};
    
//     for(size_t i = 0; i < 5; ++i)
//     {
//         auto event = sensor.produce("temperature", std::to_string(i));
//         q.enqueue(event);
//         TRACER<< event.m_deviceID << " " <<event.m_eventType << "\n";
//     }
//     pubSub.stop();

//     auto const& e1 = airCon1.getEvents();
//     auto count = e1.size();

//     ASSERT_EQUAL(count, 5);

// }
// END_TEST
BEGIN_TEST(soLoader)
    //using String = std::string;
    // using Event = iot::Event<String,String,String>;
    // using Device = iot::Device<String, String, Event>;
    // using Agent = iot::AgentFactory<Device, ConfigFile>;
END_TEST


BEGIN_SUITE(IOT PROJECT)
    TEST(temperature_sensor)
    TEST(backlog)
    TEST(controller_agent)
    TEST(send_events_to_router)
    //TEST(blocking_q)
   // TEST(pub_sub)
   //TEST(soLoader)
END_SUITE