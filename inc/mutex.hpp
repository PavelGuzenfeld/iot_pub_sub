#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include "mutex_exceptions.hpp"

namespace mt
{

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
    void exceptionThrow(int a_status, std::string a_funcName);
    void selfCheck(int a_status);

private:
    Mutex(Mutex const& a_mtx);
    Mutex& operator=(Mutex const& a_mtx);

private:
    pthread_mutex_t m_mtx;
};

struct LockGourd
{
    LockGourd(mt::Mutex& a_mutex)
    :   m_mutex(a_mutex)
    {
        m_mutex.lock();
    }

    ~LockGourd()
    {
        m_mutex.unlock();
    }

private:
    LockGourd(LockGourd const&);
    LockGourd& operator=(LockGourd const&);

private:
    Mutex& m_mutex;
};

}   //namespace mt

#endif // MUTEX_HPP