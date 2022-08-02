
#include "Mangle.h"

void Mangle::func(int /* i */)
{}

void Mangle::func(char const *)
{}

extern "C" void process_Mangle(Mangle * /* pm */)
{}

