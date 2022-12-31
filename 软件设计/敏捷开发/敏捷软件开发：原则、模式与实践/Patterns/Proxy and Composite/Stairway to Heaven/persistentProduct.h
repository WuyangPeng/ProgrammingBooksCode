#ifndef STAIRWAYTOHEAVENPERSISTENTPRODUCT_H
#define STAIRWAYTOHEAVENPERSISTENTPRODUCT_H

#include "persistentObject.h"
#include "product.h"

class PersistentProduct : public virtual Product, public PersistentObject
{
public:
    PersistentProduct(const std::string& name);
    virtual ~PersistentProduct();

protected:
    virtual void writeFields(std::ostream& s) const;

private:
    virtual void writeHeader(std::ostream& s) const;
    virtual void writeFooter(std::ostream& s) const;
};

#endif
