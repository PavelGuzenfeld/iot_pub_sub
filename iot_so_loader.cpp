#include "iot_so_loader.hpp"

#include <stdexcept>
	
namespace iot
{

SoLoader::SoLoader(std::string const& a_path)
: m_soHandle(dlopen(a_path.c_str(), RTLD_LAZY))
{
    if(!m_soHandle)
    {
        throw std::runtime_error("failed to load library " + std::string(dlerror()));
    }
}

SoLoader::~SoLoader()
{
    dlclose(m_soHandle);
}

template<typename FuncPtr>
FuncPtr SoLoader::fetch(std::string const& a_func)
{
    FuncPtr funcPtr = reinterpret_cast<FuncPtr>(dlsym(m_soHandle,a_func.c_str());
    if(!funcPtr)
    {
        throw std::runtime_error("failed to fetch function " +std::string(dlerror()
    }
    return funcPtr;
}


} // namespace iot
