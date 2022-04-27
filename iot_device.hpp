#include "iot_device.hpp"
#include "iot_event.hpp"
#include "iot_location.hpp"

#include <memory>
#include <string>

namespace iot
{

// struct Event
// {
//     /* data */
// };
// using EventsQueue = std::shared_ptr< std:queue<Event> >;

class Device
{
public:
    Device(std::string a_id, std::string a_type, Location a_location, std::string a_config);
    ~Device() = delete;

    void publish(Event& a_event);
private:
    std::string m_id;
    std::string m_type;
    Location m_location;
    std::string m_config;
};

} // namespace iot
