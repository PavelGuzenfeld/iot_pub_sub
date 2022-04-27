#include <mu_test.h>
#include "iot_event.hpp"
#include "iot_event_router.hpp"

BEGIN_TEST(router_creat)
{
    auto r = iot::EventRouter<int,int>{{{1, {11,111}}, {2,{22,222}}}};
    ASSERT_PASS();
}
END_TEST

BEGIN_SUITE(IOT PROJECT)
    TEST(router_creat)
END_SUITE