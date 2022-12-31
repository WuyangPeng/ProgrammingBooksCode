#ifndef STAIRWAYTOHEAVENASSEMBLY_H
#define STAIRWAYTOHEAVENASSEMBLY_H

#include "product.h"
#include <string>

class Assembly : public virtual Product
{
public:
    Assembly(const std::string& name, const std::string& assyCode);
    virtual ~Assembly();

    const std::string& getAssyCode() const
    {
        return itsAssyCode;
    }

private:
    std::string itsAssyCode;
};

#endif
