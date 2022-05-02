#include "mu_test.h"
#include <string>
#include <chrono>
#include <thread>
#include <blocking_queue.hpp>
#include <memory>
#include "iot_temperature_sensor.hpp"
#include "iot_backlog.hpp"
#include "iot_event.hpp"
#include "iot_event_router.hpp"
#include "iot_pub_sub.hpp"
#include "blocking_queue.hpp"
#include "thread_group.hpp"

BEGIN_TEST(temperature_sensor)
{
    using String = std::string;
    using Event = iot::Event<String,String,String>;
    using Thermometer = iot::TemperatureSensor<String, String, Event>;

    auto sensor  = Thermometer("temperature", "T-1", "Thermometer", "second floor");
    auto event = sensor.produceEvent();
    
    TRACER << "time - " << event.m_eventTime << " | data: " << event.m_data << "\n"; 
    ASSERT_EQUAL_STR(event.m_eventType.c_str(), "temperature");
    ASSERT_EQUAL_STR(event.m_deviceID.c_str(), "T-1");
    ASSERT_EQUAL_STR(event.m_deviceType.c_str(), "Thermometer");
    ASSERT_EQUAL_STR(event.m_deviceLocation.c_str(), "second floor");

}
END_TEST  

// BEGIN_TEST(send_events_to_router)
// {
//     using String = std::string;
//     using Event = iot::Event<String,String,String>;
//     using Backlog = std::shared_ptr<iot::BacklogConsumer<Event>>;
//     using Device = iot::Device<String, String, Event, Backlog, std::unique_ptr<iot::Controller<String>>>;
//     using Map = std::map<String, std::vector<Device>>;
//     using Router = iot::EventRouter<String,Event,Device,Map&>;

//     auto sensor = Device{"temperature sensor 1","heat_sensor","floor 1", "no config"};

    // auto eventSubscribers = Map();
    // eventSubscribers["temperature"].emplace_back(Device{"con 1","air_con","floor 1", "temp > 30"});
    // eventSubscribers["temperature"].emplace_back(Device{"con 2","air_con","floor 1", "temp > 30"});
    // auto router = Router{eventSubscribers};

    // for(size_t i = 0; i < 5; ++i)
    // {
    //     auto event = sensor.produce("temperature", std::to_string(i));
    //     TRACER<< "Device id - " << event.m_deviceID << "| event: " << event.m_eventType << "\n";
    //     router.rout(event);
    // }

    // auto subscribers = eventSubscribers["temperature"];
    // for(auto s: subscribers)
    // {
    //     auto count = s.getEvents().size();
    //     ASSERT_EQUAL(count, 5);
    // }
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

BEGIN_SUITE(IOT PROJECT)
    TEST(temperature_sensor)
    //TEST(send_events_to_router)
   // TEST(pub_sub)
END_SUITE