#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP

namespace cpp
{

struct Abstract
{
protected:
    Abstract() = default;
    virtual ~Abstract() = default;
    Abstract(Abstract const&) = delete;
    Abstract& operator=(Abstract const&) = delete;    
};

}// namespace cpp

#endif //ABSTRACT_HPP