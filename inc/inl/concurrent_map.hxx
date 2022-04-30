#ifndef THREAD_MAP_HXX
#define THREAD_MAP_HXX

#include <map>

template<typename K, typename V>
struct MapData
{
    mutable mt::Mutex m_mtx;
    std::map<K, V> m_dataMap;
};

template<typename K, typename V, typename HF>
mt::ConcurrentMap<K, V, HF>::ConcurrentMap(size_t a_concurrency)
:   m_concurrency(a_concurrency)
, 	m_hash()
,   m_maps(m_concurrency)
{

}

template<typename K, typename V, typename HF>
bool mt::ConcurrentMap<K, V, HF>::creat(K const& a_key, V const& a_Ref)
{
	auto& m = map(a_key);
	LockGourd g(m.m_mtx);
	
	auto it = m.m_dataMap.find(a_key);
	if(it != m.m_dataMap.end())
	{
		return false;
	}
	m.m_dataMap[a_key] = a_Ref;
	return true;
}

template<typename K, typename V, typename HF>
bool mt::ConcurrentMap<K, V, HF>::read(K const& a_key, V& a_retRef) const
{
	auto& m = map(a_key);
	LockGourd g(m.m_mtx);
	
	auto it = m.m_dataMap.find(a_key);
	if(it == m.m_dataMap.end())
	{
		return false;
	}
	a_retRef = it->second;
	return true;
}

template<typename K, typename V, typename HF>
bool mt::ConcurrentMap<K, V, HF>::update(K const& a_key, std::function<V(V)> a_updator)
{
	auto& m = map(a_key);
	LockGourd g(m.m_mtx);
	
	auto it = m.m_dataMap.find(a_key);
	if(it == m.m_dataMap.end())
	{
		return false;
	}
	it->second = a_updator(it->second);
	return true;
}

template<typename K, typename V, typename HF>
void mt::ConcurrentMap<K, V, HF>::erase(K const& a_key)
{
	auto& m = map(a_key);
	LockGourd g(m.m_mtx);
	
	auto it = m.m_dataMap.find(a_key);
	if(it == m.m_dataMap.end())
	{
		return;
	}
	erase(it);
}

template<typename K, typename V, typename HF>
bool mt::ConcurrentMap<K, V, HF>::contains(K const& a_key) const
{
	auto& m = map(a_key);
	LockGourd g(m.m_mtx);
	return m.m_dataMap.count(a_key) == 1;
}

//private
template<typename K, typename V, typename HF>
MapData<K, V>const& mt::ConcurrentMap<K, V, HF>::map(K const& a_key) const
{
	auto h = m_hash(a_key);
	auto i = h % m_concurrency;
	auto& m = m_maps[i];
    return m;
}

template<typename K, typename V, typename HF>
MapData<K, V>& mt::ConcurrentMap<K, V, HF>::map(K const& a_key)
{
	auto h = m_hash(a_key);
	auto i = h % m_concurrency;
	auto& m = m_maps[i];
    return m;
}

#endif  // THREAD_MAP_HPP