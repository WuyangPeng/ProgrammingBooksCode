#include "assembly.h"

Assembly::Assembly(const std::string& name, const std::string& assyCode)
  :Product(name), itsAssyCode(assyCode)
{
}

Assembly::~Assembly()
{
}
