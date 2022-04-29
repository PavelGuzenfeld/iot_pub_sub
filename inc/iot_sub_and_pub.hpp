#pragma once

#include <memory> // shared_ptr
#include "iot_decode.hpp"
#include "iot_encode.hpp"
#include "iot_event.hpp"

namespace iot
{
    
class SubAndPub
{

public:
    ~SubAndPub() = default;

    virtual void consume(Event a_event, );
    virtual void publish();

private:
    std::shared_ptr<Decode> m_decode;
    std::shared_ptr<Encode> m_encode;
};

} // namespace iot
