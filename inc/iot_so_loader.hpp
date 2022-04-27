#pragma once

#include <dlfcn.h>
#include <string>

namespace iot
{
class SoLoader
{
public:
    explicit SoLoader(std::string const& a_path);
    ~SoLoader();

    SoLoader(SoLoader const& a_src) = default;
    SoLoader& operator=(SoLoader const& a_src) = default;
    
    template<typename FUNCPTR>
    FUNCPTR fetch(std::string const& a_func);

public:
    //TODO: switch to unique_ptr
    void* m_soHandle;
};

} // namespace iot
