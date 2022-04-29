#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "iot_device.hpp"

namespace iot
{

template<typename Device>
class AgentManager
{
public:
    AgentManager() = default;

    AgentManager(AgentManager const& a_src) = delete;
    AgentManager& operator=(AgentManager const& a_src) = delete;
    ~AgentManager() = default;

    std::shared_ptr<Device> findAgent(std::string a_agentId);
    void add(std::string a_agentId);
    void remove(std::string a_agentId);

private:
    std::unordered_map<std::string, std::shared_ptr<Device> > m_agentMap;
};

#include "inl/iot_agent_manager.hxx"

} // namespace iot
