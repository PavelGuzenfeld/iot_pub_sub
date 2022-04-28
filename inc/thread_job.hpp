#ifndef THREAD_JOB_HPP
#define THREAD_JOB_HPP

namespace mt
{

struct ThreadJob
{
public:
    ThreadJob(){}
    virtual ~ThreadJob(){}

    virtual void* operator()(void* a_arg) = 0;

private:
    ThreadJob(ThreadJob const& o);
    ThreadJob& operator=(ThreadJob const& o);
};

//#include "inl/thread_job.hxx"

} // namespace mt

#endif // THREAD_JOB_HPP