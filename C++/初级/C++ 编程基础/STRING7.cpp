#include "xstring.h"

xstring::xstring(const xstring& Str)
: string(Str)
{
}

xstring::xstring(short Length, char Ch)
: string(Length,Ch)
{
}

xstring::xstring(char* p)
: string(p)
{
}

short xstring::find_nocase(const xstring& Str)
{
    short i;
    short length = m_Length-1;
    short strlength = Str.m_Length-1;

    for (i = 0; i < length-strlength+1; i ++)
      {
      if (strnicmp(m_Data+i,Str.m_Data,strlength) == 0)
        return i;
      }

    return -1;
}

bool xstring::less_nocase(const xstring& Str)
{
    short Result;
    short CompareLength;

    if (Str.m_Length < m_Length)
        CompareLength = Str.m_Length;
    else
        CompareLength = m_Length;

    Result = strnicmp(m_Data,Str.m_Data,CompareLength);

    if (Result < 0)
        return true;

    if (Result > 0)
        return false;

    if (m_Length < Str.m_Length)
        return true;

    return false;
}

