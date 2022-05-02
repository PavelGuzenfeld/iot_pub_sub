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
    using STRING = std::string;
public:
    AgentFactory(std::share_ptr<Device> const& a_agents,std::shared_ptr<ConfigReader> const& a_configReader);

    AgentFactory(AgentFactory const& a_src) = delete;
    AgentFactory& operator=(AgentFactory const& a_src) = delete;
    ~AgentFactory() = default;

    void createAgents(std::string const& a_configFilePath);

private:
    typedef SoftwareAgent* (*AgentFactory)(STRING const& a_deviceId, STRING const& a_type, int const& a_floor, unsigned int const& a_floor, STRING const& a_config);

private:
    std::shared_ptr<AgentManager> m_agents;
    std::shared_ptr<ConfigReader> m_configReader;
};

} // namespace iot

#include "inl/iot_agent_factory.hxx"
