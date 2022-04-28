#ifndef MUTEX_EXCEPTIONS_HPP
#define MUTEX_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace mt
{

struct MutexRuntimeError : std::runtime_error
{
    MutexRuntimeError(std::string a_what);
};

struct TryAgainError : MutexRuntimeError
{
    //EAGAIN
    TryAgainError(std::string a_what);    
};

struct NoMemoryError : MutexRuntimeError
{
    // ENOMEM
    NoMemoryError(std::string a_what);
};

struct PermissioError : MutexRuntimeError
{
    // EPERM
    PermissioError(std::string  a_what);
};

struct BusyError : MutexRuntimeError
{
    // EBUSY
    BusyError(std::string a_what);
};

struct InvalidValue : MutexRuntimeError
{
    // EINVAL
    InvalidValue(std::string a_what);
};

struct NotRecoverable : MutexRuntimeError
{
    // ENOTRECOVERABLE
    NotRecoverable(std::string a_what);
};

struct OwnerDead : MutexRuntimeError
{
    // EOWNERDEAD
    OwnerDead(std::string a_what);
};

struct DeadLock : MutexRuntimeError
{
    //EDEADLK
    DeadLock(std::string a_what);
};

} // namespace mt

#endif // MUTEX_EXCEPTIONS_HPP