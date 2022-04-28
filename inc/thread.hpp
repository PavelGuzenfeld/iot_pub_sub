#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>

namespace mt
{

    template <typename T>
    //requires operator()
    class Thread
    {
    public:
        Thread(T& a_funcObj, bool a_detach = false);
        //Default ctor
        Thread(bool a_detach = false);
        //Move ctor
        Thread(Thread const &a_thread);
        ~Thread();

        void detach();
        bool isDetach() const;

        void join();
        bool operator==(Thread const &a_rhs) const;
        bool operator!=(Thread const &a_rhs) const;

        static pthread_t self();
        static void join(pthread_t);

    private:
        static void* routine(void* a_arg);
        Thread &operator=(Thread const &a_thread);

    private:
        pthread_t m_tid;
        bool m_joined;
        bool m_detach;
    };

#include "inl/thread.hxx"

} // namspace mt

#endif // THREAD_HPP