#include "array.hpp"
#include <cassert>

namespace cpp
{
    
//public
template<typename T>
Array<T>::Array(size_t a_size)
:   m_size(a_size)
,   m_array(new T[m_size + 1]) //sentinel
{
    invariantCheck();
}

template< typename T>
Array<T>::Array::~Array()
{
    delete[] m_array;
}

template<typename T>
Array<T>::Array(Array const& a_rhs)
:   m_size(a_rhs.m_size)
,   m_array(new T[m_size + 1]) //sentinel
{
    copy<T>(m_array, &a_rhs.m_array[0], &a_rhs.last() );
    invariantCheck();
}

template<typename T>
Array<T>& Array<T>::operator=(Array const& a_rhs)
{
    T* oldArr = m_array;
    
    m_size = a_rhs.m_size;
    m_array = new T[m_size + 1]; //sentinel
    copy<T>(m_array, &a_rhs.m_array[0], &a_rhs.last() );
    
    delete[] oldArr;
    invariantCheck();

    return *this;
}

template<typename T>
void Array<T>::at(size_t a_index,int a_data)
{
    assert(a_index < m_size);

    m_array[a_index] = a_data;

    invariantCheck();
}

template<typename T>
T Array<T>::at(size_t a_index) const
{
    assert(a_index < m_size);
    return m_array[a_index];
}

template<typename T>
T const& Array<T>::operator[](size_t a_index) const
{
    return m_array[a_index];
}

template<typename T>
T& Array<T>::operator[](size_t a_index)
{
    return m_array[a_index];
}

template<typename T>
size_t Array<T>::size() const
{
    return m_size;
}

template<typename T>
T& Array<T>::last() const
{
    return m_array[m_size];
}
    
//private
template<typename T>
void Array<T>::Array::invariantCheck() const
{
    assert(m_array);
    //TODO: check sentinel did not change
}

//global
template<class T>
T* copy(T* a_dest,T const* a_begin, T const* a_end)
{
    assert(a_dest);
    assert(a_begin);
    assert(a_end);

    while (a_begin != a_end)   
    {
        *a_dest = *a_begin;
        ++a_begin;
        ++a_dest;
    }

    return a_dest;
}

} // namespace cpp