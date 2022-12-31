#include "persistentObject.h"

PersistentObject::~PersistentObject()
{
}

void PersistentObject::write(std::ostream& s) const
{
    writeHeader(s);
    writeFields(s);
    writeFooter(s);
    s << std::ends;
}
