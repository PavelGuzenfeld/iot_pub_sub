#pragma once

#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include "ini.h"
#include "iot_device_config.hpp"

namespace iot
{

class IniReader
{
using String = std::string;
using NameValuePair = std::pair<String, String>;
using NameValPairs = std::vector<NameValuePair>;
using ParsedMap = std::unordered_map<String, NameValPairs>;

public:
    IniReader() = default;
    IniReader(IniReader const& a_src) = delete;
    IniReader& operator=(IniReader const& a_src) = delete;
    ~IniReader() = default;

    DeviceConfig readConfig(String const& a_configFile);

private:
    static int handler(void* a_sectionsMap, const char* a_section, const char* a_name, const char* a_value);
    DeviceConfig CreateDeviceFromMap();

private:
    ParsedMap m_parsedMap;
    std::vector<DeviceConfig> m_devices;
};

} // namespace iot
