#ifndef THREAD_JOB_HPP
#define THREAD_JOB_HPP

namespace mt
{

struct ThreadJob
{
public:
    ThreadJob() = default;
    virtual ~ThreadJob() = default;

    virtual void* operator()(void* a_arg) = 0;

private:
    ThreadJob(ThreadJob const& o);
    ThreadJob& operator=(ThreadJob const& o);
};

} // namespace mt

#endif // THREAD_JOB_HPP