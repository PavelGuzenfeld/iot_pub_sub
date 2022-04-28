#ifndef CONCURRENT_MAP_HPP
#define CONCURRENT_MAP_HPP

#include <map>
#include <string>
#include <functional>
#include "mutex.hpp"
#include "array.hpp"

namespace mt
{

template<typename k, typename V>
struct MapData;

template<typename K, typename V, typename HF = std::hash<K>>
class ConcurrentMap
{
public:
    ConcurrentMap(size_t a_concurrency);

    bool creat(K const& a_key, V const& a_Ref);
    bool read(K const& a_key, V& a_retRef) const;
    bool update(K const& a_key, std::function<V(V)> a_updator);
    void erase(K const& a_key);

    bool contains(K const& a_key ) const;

private:
    MapData<K, V>const& map(K const& a_key) const;
    MapData<K, V>& map(K const& a_key);

private:
    size_t m_concurrency;
    HF m_hash;
    cpp::Array<MapData<K, V>> m_maps;
};

#include "inl/concurrent_map.hxx"

}   // namespace mt

#endif  // CONCURRENT_MAP_HPP

//TODO: add exceptions