#ifndef THREAD_Group_HPP
#define THREAD_Group_HPP

#include <vector>
#include "thread.hpp"

namespace mt
{

template<typename F>
//requires opperator()
struct ThreadGroup
{
    ThreadGroup(std::vector<F>& a_funcObjVec);
    ThreadGroup(F& a_funcObj, size_t const a_threads);

    void join();

private:
    ThreadGroup& operator=(ThreadGroup const& a_group);

private:
    std::vector<Thread<F> > m_threads;
};

#include "inl/thread_group.hxx"

} // namspace mt

#endif // THREAD_Group_HPP