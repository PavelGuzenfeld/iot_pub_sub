#ifndef QUEUE_EXCEPTIONS_HPP
#define QUEUE_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace cpp
{

struct QueueError : std::runtime_error
{
    QueueError(std::string a_what)
    :   runtime_error(a_what)
    {

    }
};

struct QueueBadAlloc : QueueError
{
    QueueBadAlloc(std::string a_what)
    :   QueueError(a_what)
    {

    }
};

struct QueueUnderflow : QueueError
{
    QueueUnderflow(std::string a_what)
    :   QueueError(a_what)
    {

    }
};

struct QueueOverflow : QueueError
{
    QueueOverflow(std::string a_what)
    :   QueueError(a_what)
    {

    }
};

struct QueueEmpty : QueueError
{
    QueueEmpty(std::string a_what)
    :   QueueError(a_what)
    {

    }
};

} // namespace cpp

#endif // QUEUE_EXCEPTIONS_HPP