#ifndef THREADS_HXX
#define THREADS_HXX

#include <cassert>

template<typename T>
void* mt::Thread<T>::routine(void* a_arg)
{
    T& func = *static_cast<T*>(a_arg);
    return func(0);
}

template<typename T>
mt::Thread<T>::Thread(T& a_funcObj, bool a_detach)
:   m_tid()
,   m_joined(false)
,   m_detach(a_detach)
{
    int s = ::pthread_create (&m_tid, 0, Thread<T>::routine, &a_funcObj);
    assert(s == 0);

    if(m_detach == true)
    {
        int s = pthread_detach(m_tid);
        assert(s == 0);
    }
}

static void* defaultFunc(void* a_arg)
{
    return a_arg;
}

template<typename T>
mt::Thread<T>::Thread(bool a_detach)
:   m_tid()
,   m_joined(false)
,   m_detach(a_detach)
{
    int s = ::pthread_create (&m_tid, 0, defaultFunc, 0);
    assert(s == 0);

    if(m_detach == true)
    {
        int s = pthread_detach(m_tid);
        assert(s == 0);
    }
}

template<typename T>
mt::Thread<T>::Thread(Thread<T> const &a_thread)
:   m_tid(a_thread.m_tid)
,   m_joined(a_thread.m_joined)
,   m_detach(a_thread.m_detach)
{
    Thread& t = const_cast<Thread<T>&>(a_thread);
    t.m_tid = 0;
    if(t.m_detach == false)
    {
        t.m_joined = true;
    }
}

template<typename T>
mt::Thread<T>::~Thread()
{
    assert(m_joined == true || m_detach == true);
}

template<typename T>
void mt::Thread<T>::detach()
{
    assert(m_detach == false);
    int s = pthread_detach(m_tid);
    assert(s == 0);

    m_detach = true;
}

template<typename T>
bool mt::Thread<T>::operator==(Thread const& a_rhs) const
{
    return pthread_equal(m_tid, a_rhs.m_tid) != 0;
}

template<typename T>
bool mt::Thread<T>::operator!=(Thread const &a_rhs) const
{
    return !operator==(a_rhs);
}

template<typename T>
void mt::Thread<T>::join()
{
    assert(m_detach == false);
    assert(m_joined == false);

    void* ret = 0;
    int s = pthread_join(m_tid, &ret);
    assert(s == 0);
    m_joined = true;
}

//static
template<typename T>
pthread_t mt::Thread<T>::self()
{
    return pthread_self();
}

//static   
template<typename T>
void mt::Thread<T>::join(pthread_t a_thread)
{
    assert(pthread_equal(pthread_self(), a_thread) != 0);

    void* ret = 0;
    int s = pthread_join(a_thread, &ret);
    assert(s == 0);
}
 
#endif // THREADS_HXX