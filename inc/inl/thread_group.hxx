#ifndef THREAD_Group_HXX
#define THREAD_Group_HXX
#include <iostream>

template<typename F>
mt::ThreadGroup<F>::ThreadGroup(std::vector<F>& a_funcObjVec)
:m_threads()
{
    m_threads.reserve(a_funcObjVec.size() );
    size_t const size = a_funcObjVec.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_threads.push_back(a_funcObjVec[i]);
    }
}

template<typename F>
mt::ThreadGroup<F>::ThreadGroup(F& a_funcObj, size_t const a_threads)
{
    m_threads.reserve(a_threads);
    for(size_t i = 0; i < a_threads; ++i)
    {
        m_threads.push_back(a_funcObj);
    }

}


template<typename F>
void mt::ThreadGroup<F>::join()
{
    size_t const size = m_threads.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_threads[i].join();
    }
}

#endif // THREAD_Group_HXX