#include "string7x.h"

string::string(short Length)
: m_Length(Length + 1),
  m_Data(new char [m_Length])
{
    char Ch = 0;
    memset(m_Data,Ch,Length);
    m_Data[Length] = 0;
}

string::string(short Length, char Ch)
: m_Length(Length + 1),
  m_Data(new char [m_Length])
{
    memset(m_Data,Ch,Length);
    m_Data[Length] = 0;
}

