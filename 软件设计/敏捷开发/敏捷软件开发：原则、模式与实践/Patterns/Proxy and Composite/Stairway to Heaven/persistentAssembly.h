#ifndef STAIRWAYTOHEAVENPERSISTENTASSEMBLY_H
#define STAIRWAYTOHEAVENPERSISTENTASSEMBLY_H

#include "assembly.h"
#include "persistentProduct.h"

class PersistentAssembly : public Assembly, public PersistentProduct
{
public:
    PersistentAssembly(const std::string& name, const std::string& assyCode);
    virtual ~PersistentAssembly();

protected:
    virtual void writeFields(std::ostream& s) const;

private:
    virtual void writeHeader(std::ostream& s) const;
    virtual void writeFooter(std::ostream& s) const;
};

#endif
