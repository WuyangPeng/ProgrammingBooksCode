#include "xstring.h"

using std::string;

xstring::xstring()
: string()
{
}

xstring::xstring(const xstring& Str)
: string(Str)
{
}

xstring::xstring(const string& Str)
: string(Str)
{
}

xstring::xstring(char* p)
: string(p)
{
}

xstring::xstring(unsigned Length, char Ch)
: string(Length, Ch)
{
}

xstring::xstring(unsigned Length)
: string(Length, ' ')
{
}

short xstring::find_nocase(const xstring& Str)
{
  short i;
  short thislength = size();
  short strlength = Str.size();
  const char* thisdata = c_str();
  const char* strdata = Str.c_str();

  for (i = 0; i < thislength-strlength+1; i ++)
    {
    if (strnicmp(thisdata+i,strdata,strlength) == 0)
      return i;
    }

  return -1;
}

bool xstring::less_nocase(const xstring& Str)
{
  short Result;
  short CompareLength;

  short thislength = size();
  short strlength = Str.size();
  const char* thisdata = c_str();
  const char* strdata = Str.c_str();

  if (strlength < thislength)
      CompareLength = strlength;
  else
      CompareLength = thislength;

  Result = strnicmp(thisdata,strdata,CompareLength);

  if (Result < 0)
      return true;

  if (Result > 0)
      return false;

  if (thislength < strlength)
      return true;

  return false;
}

