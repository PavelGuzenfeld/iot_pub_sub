#include "iot_so_loader.hpp"
#include "iot_agent_manager.hpp"

template<typename Device, typename ConfigReader>
AgentFactory<Device, ConfigReader>::AgentFactory(std::share_ptr<Device> const& a_agents, std::shared_ptr<ConfigReader> const& a_configReader)
: m_agents(a_agents)
, m_configReader(a_configReader)
{

}

template<typename Device, typename ConfigReader>
void iot::AgentFactory<Device, ConfigReader>::createAgents(std::string const& a_configFile)
{
    Device device = m_configReader->readConfig(a_configFile);
    std::for_each(device.begin(), device.end(), [&](Device const& a_device)
    {
        try
        {
            SoLoader dlib(a_device.m_soHandle);
            AgentFactory agent = dlib.fetch<AgentFactory>("CreateAgent"));
            shared_ptr<SoftwareAgent> newAgent = std::shared_ptr<SoftwareAgent>((*agent)(a_device.m_type, a_device.m_floor, a_device.m_room, a_device.m_config));
            m_agents->add(newAgent);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}