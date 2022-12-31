#ifndef STAIRWAYTOHEAVENPERSISTENTOBJECT_H
#define STAIRWAYTOHEAVENPERSISTENTOBJECT_H

#include <iostream>

class PersistentObject
{
public:
    virtual ~PersistentObject();
    virtual void write(std::ostream&) const;

protected:
    virtual void writeFields(std::ostream&) const = 0;

private:
    virtual void writeHeader(std::ostream&) const = 0;
    virtual void writeFooter(std::ostream&) const = 0;
};

#endif
