#include <mu_test.h>
#include <string>
#include "iot_event.hpp"
#include "iot_event_router.hpp"
#include "iot_device.hpp"

BEGIN_TEST(router_creat)
{
    auto r = iot::EventRouter<int,int>{{{1, {11,111}}, {2,{22,222}}}};
    ASSERT_PASS();
}
END_TEST

BEGIN_TEST(device)
{
    auto event = iot::Device<std::string, std::string, std::string>{"id - device1","type - heat"," location - floor 1", " no config"};
    ASSERT_PASS();
}
END_TEST

BEGIN_SUITE(IOT PROJECT)
    TEST(router_creat)
    TEST(device)
END_SUITE