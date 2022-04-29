#include <string>
#include <memory>
#include "iot_so_loader.hpp"
#include "iot_agent_manager.hpp"

template<typename Device, typename ConfigReader>
AgentFactory<Device, ConfigReader>::AgentFactory(std::share_ptr<Device> a_agents,std::shared_ptr<ConfigReader> a_configReader)
: m_agents(a_agetns)
, m_configReader(a_configReader)
{

}

template<typename Device, typename ConfigReader>
void AgentFactory<Device, ConfigReader>::createAgents(std::string a_configFilePath)
{

}