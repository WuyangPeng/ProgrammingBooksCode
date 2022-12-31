#include "persistentProduct.h"

PersistentProduct::PersistentProduct(const std::string& name)
    : Product(name)
{
}

PersistentProduct::~PersistentProduct()
{
}

void PersistentProduct::writeHeader(std::ostream& s) const
{
    s << "<PRODUCT>";
}

void PersistentProduct::writeFooter(std::ostream& s) const
{
    s << "</PRODUCT>";
}

void PersistentProduct::writeFields(std::ostream& s) const
{
    s << "<NAME>" << getName() << "</NAME>";
}
