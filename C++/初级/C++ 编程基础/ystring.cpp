#include <string>
#include "stringy.h"
using namespace std;

xstring::xstring(short Length)
: string(Length,0)
{
}

xstring::xstring(short Length, char Ch)
: string(Length, Ch)
{
}

