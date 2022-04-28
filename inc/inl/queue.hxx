#ifndef QUEUE_HXX
#define QUEUE_HXX

#include <cassert> //assert()

template <typename T>
cpp::Queue<T>::Queue(size_t a_cap)
try
:   m_capacity(a_cap)
,   m_data(m_capacity)
,   m_size()
,   m_head()
,   m_tail()
{
    enverientCheck();
}
catch(...)
{
    throw QueueBadAlloc("Queue Bad alloc");
}

template <typename T>
void cpp::Queue<T>::enqueue(T const& a_element)
{
    if(isFull() == true)
    {
        throw QueueOverflow("queue overflow");
    }
    m_data[m_tail] = a_element;
    m_tail = next(m_tail);
    ++m_size;
    
    enverientCheck();
}

template <typename T>
void cpp::Queue<T>::dequeue()
{
    if(isEmpty() == true)
    {
        throw QueueUnderflow("queue underflow");
    }
    m_head = next(m_head);
    --m_size;

    enverientCheck();
}

template <typename T>
T const& cpp::Queue<T>::first() const
{
    if(isEmpty() == true)
    {
        throw QueueEmpty("queue is empty");
    }
    return m_data[m_head];
}

template <typename T>
void cpp::Queue<T>::clear()
{
    m_size = 0;
    m_head = 0;
    m_tail = 0;
    enverientCheck();
}

template <typename T>
size_t cpp::Queue<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
size_t cpp::Queue<T>::size() const
{
    return m_size;
}

template <typename T>
bool cpp::Queue<T>::isFull() const
{
    return m_size == m_capacity;
}

template <typename T>
bool cpp::Queue<T>::isEmpty() const
{
    return m_size == 0;
}

//private
template <typename T>
size_t cpp::Queue<T>::next(size_t a_index) const
{
    return (a_index + 1) % m_capacity;
}

template <typename T>
void cpp::Queue<T>::enverientCheck() const
{
    assert(m_head < m_capacity);
    assert(m_tail < m_capacity);
    assert(m_size <= m_capacity);
}

#endif // QUEUE_HXX