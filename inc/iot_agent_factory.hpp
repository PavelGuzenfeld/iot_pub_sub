#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "iot_device.hpp"

namespace iot
{

template<typename Device, typename ConfigReader>
class AgentFactory
{
public:
    AgentFactory(std::share_ptr<Device> a_agents,std::shared_ptr<ConfigReader> a_configReader);

    AgentFactory(AgentFactory const& a_src) = delete;
    AgentFactory& operator=(AgentFactory const& a_src) = delete;
    ~AgentFactory() = default;

    void createAgents(std::string a_configFilePath);

private:
    std::shared_ptr<Device> m_agents;
    std::shared_ptr<ConfigReader> m_configReader;
};

#include "inl/iot_agent_factory.hxx"

} // namespace iot
