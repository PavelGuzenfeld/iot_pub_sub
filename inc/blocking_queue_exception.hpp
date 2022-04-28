#ifndef BLOCKING_QUEUE_EXCEPTION_HPP
#define BLOCKING_QUEUE_EXCEPTION_HPP

#include <stdexcept>
#include <string>
namespace mt
{

struct BlockingQueueError : std::runtime_error
{
    BlockingQueueError(std::string& a_what)
    :   std::runtime_error(a_what)
    {

    }
};

struct BlockingQueueCtorFailed : BlockingQueueError
{
    BlockingQueueCtorFailed(std::string& a_what)
    :BlockingQueueError(a_what)
    {

    }
};

struct BlockingQueueEnqueueFailed : BlockingQueueError
{
    BlockingQueueEnqueueFailed(std::string& a_what)
    :BlockingQueueError(a_what)
    {

    }
};

struct BlockingQueueDequeueFailed : BlockingQueueError
{
    BlockingQueueDequeueFailed(std::string& a_what)
    :BlockingQueueError(a_what)
    {

    }
};

struct BlockingQueueFirstFailed : BlockingQueueError
{
    BlockingQueueFirstFailed(std::string& a_what)
    :BlockingQueueError(a_what)
    {

    }
};

}   // namespace mt

#endif // BLOCKING_QUEUE_EXCEPTION