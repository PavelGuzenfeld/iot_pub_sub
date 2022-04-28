#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

namespace cpp
{

template< typename T>
class Array
{
public:
    Array(size_t a_size = 64); // cache lines
    
    ~Array();
    Array(Array const& a_rhs);
    Array& operator=(Array const& a_rhs);

    void at(size_t a_index,int a_value);
    T at(size_t a_index) const;

    T const& operator[](size_t a_index) const;
    T& operator[](size_t a_index);

    size_t size() const;
    T& last() const;
    
private:
    void invariantCheck() const;

private:
    size_t m_size;
    T *m_array;
};

template<class T>
T* copy(T* a_dest,T const* a_begin, T const* a_end);

} // namespace cpp

#include "inl/array.hxx"

#endif//ARRAY_HPP