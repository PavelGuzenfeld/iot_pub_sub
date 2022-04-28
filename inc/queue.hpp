#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "array.hpp"
#include "queue_exceptions.hpp"

namespace cpp
{

template <typename T>
class Queue   
{
public:
    Queue( size_t a_capacity = 64 ); // to fit to one cache line

    void enqueue(T const& a_element);
    void dequeue();
    T const& first() const;
    void clear();

    size_t capacity() const;
    size_t size() const;

    bool isFull() const;
    bool isEmpty() const;

    void flipDirection() const;
    
private:
    size_t next(size_t a_indx) const;
    void enverientCheck() const;

private:
    size_t m_capacity;
    Array<T> m_data;
    size_t m_size;
    size_t m_head;
    size_t m_tail;
};

#include "inl/queue.hxx"

} // namespace cpp

#endif //QUEUE_HPP