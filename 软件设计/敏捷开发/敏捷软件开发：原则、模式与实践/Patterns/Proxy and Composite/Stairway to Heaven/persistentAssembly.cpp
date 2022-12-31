#include "persistentAssembly.h"

PersistentAssembly::PersistentAssembly(const std::string& name, const std::string& assyCode)
    : Assembly(name, assyCode), PersistentProduct(name), Product(name)
{
}

PersistentAssembly::~PersistentAssembly()
{
}

void PersistentAssembly::writeHeader(std::ostream& s) const
{
    s << "<ASSEMBLY>";
}

void PersistentAssembly::writeFooter(std::ostream& s) const
{
    s << "</ASSEMBLY>";
}

void PersistentAssembly::writeFields(std::ostream& s) const
{
    PersistentProduct::writeFields(s);
    s << "<ASSYCODE>" << getAssyCode() << "</ASSYCODE>";
}
