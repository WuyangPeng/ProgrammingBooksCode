#ifndef STAIRWAYTOHEAVENPRODUCT_H
#define STAIRWAYTOHEAVENPRODUCT_H

#include <string>

class Product
{
public:
    Product(const std::string& name);
    virtual ~Product();
    const std::string& getName() const
    {
        return itsName;
    }

private:
    std::string itsName;
};

#endif
