#include "iot_ini_reader.hpp"
#include <string>
namespace iot
{
DeviceConfig IniReader::readConfig(String const& a_configFileName)
{
    ini_parse(a_configFileName.c_str(), handler, &m_parsedMap);

    return CreateDeviceFromMap();
}

int IniReader::handler(void* a_sectionsMap, const char* a_section, const char* a_name, const char* a_value)
{
    ParsedMap* pm = static_cast<ParsedMap*>(a_sectionsMap);
    String section(a_section);
    String name(a_name);
    String value(a_value);

    if(pm->find(section) == pm->end())
    {
        pm->insert({section, NameValPairs()});
    }
    (*pm)[section].push_back(std::make_pair(name, value));
}

DeviceConfig IniReader::CreateDeviceFromMap()
{
    for(auto const& pair : m_parsedMap)
    {
        DeviceConfig device;
        device.m_id = pair.first;
        std::for_each(pair.second.begin(), pair.second.end(), [&](NameValuePair const& a_nvPair)
        {
            if(a_nvPair.first == "type")
            {
                device.m_type = a_nvPair.second;
            }
            else if(a_nvPair.first == "room")
            {
                device.m_room = std::stoul(a_nvPair.second); 
            }
            else if(a_nvPair.first == "floor")
            {
                device.m_floor = std::stoul(a_nvPair.second);
            }
            else if(a_nvPair.first == "log")
            {
                device.m_log = a_nvPair.second;
            }
            else if(a_nvPair.first == "config")
            {
                device.m_config = a_nvPair.second;
            }
            else if(a_nvPair.first == "so")
            {
                device.m_so = a_nvPair.second;
            }

        });
    m_devices.push_back(device);
    }
}

} // namespace iot
