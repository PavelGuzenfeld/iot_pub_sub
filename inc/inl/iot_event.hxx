#ifndef IOT_EVENT_HXX
#define IOT_EVENT_HXX

template<typename STRING,typename TIME, typename LOCATION>
constexpr bool Event<STRING,TIME,LOCATION>::operator()( const Event& a_lhs, const Event& a_rhs ) const
{
    return a_lhs.m_id < a_rhs.m_id;
}

#endif // IOT_EVENT_HXX