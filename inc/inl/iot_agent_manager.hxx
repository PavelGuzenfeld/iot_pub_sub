#include <string>
#include <memory>

template<typename Device>
std::shared_ptr<Device> AgentManager<Device>::findAgent(std::string const& a_agentId)
{
    if (m_agentMap.find() == m_agentMap.end())
    {
        return nullptr;
    }
    return m_agentMap[a_agentId];
}

template<typename Device>
void AgentManager::add(std::string const& a_agentId)
{
   find(this->m_id) = a_agentId;
}

template<typename Device>
void AgentManager::remove(std::string const& a_agentId)
{
    m_agentMap.erase(a_agentId);
}


// private:
//     std::unordered_map<std::string, std::shared_ptr<Device> m_agentMap;