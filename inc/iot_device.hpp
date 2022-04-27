#include "iot_event.hpp"

namespace iot
{

template<typename STRING, typename LOCATION, typename EVENT>
class Device
{
public:
    Device(STRING a_id, STRING a_type, LOCATION a_location, STRING a_config);

    EVENT publish();
    void subscribe(EVENT const& a_event);

private:
    STRING m_id;
    STRING m_type;
    LOCATION m_location;
};

} // namespace iot
