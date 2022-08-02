#include <iostream>
#include <cstring>
#include "string5.h"

string::string()
: m_Length(1),
  m_Data(new char [m_Length])
{
    memcpy(m_Data,"",m_Length);
}

string::string(const string& Str)
: m_Length(Str.m_Length),
  m_Data(new char [m_Length])
{
    memcpy(m_Data,Str.m_Data,m_Length);
}

string::string(char* p)
: m_Length(strlen(p) + 1),
  m_Data(new char [m_Length])
{
    memcpy(m_Data,p,m_Length);
}

string& string::operator = (const string& Str)
{
  char* temp = new char[Str.m_Length];
  
  m_Length = Str.m_Length;
  memcpy(temp,Str.m_Data,m_Length);
  delete [ ] m_Data;
  
  m_Data = temp;
  
  return *this;
}

string::~string()
{
    delete [ ] m_Data;
}

short string::GetLength()
{
    return m_Length-1;
}

bool string::operator < (const string& Str)
{
    short i;
    bool Result;
    bool ResultFound;
    short CompareLength;

    if (Str.m_Length < m_Length)
        CompareLength = Str.m_Length;
    else
        CompareLength = m_Length;

    ResultFound = false;
    for (i = 0; (i < CompareLength) && (ResultFound == false); i ++)
        {
        if (m_Data[i] < Str.m_Data[i])
            {
            Result = true;
            ResultFound = true;
            }
        else
            {
            if (m_Data[i] > Str.m_Data[i])
                {
                Result = false;
                ResultFound = true;
                }
            }
        }

    if (ResultFound == false)
        {
        if (m_Length < Str.m_Length)
            Result = true;
        else
            Result = false;
        }

    return Result;
}

bool string::operator == (const string& Str)
{
    short Result;
    if (m_Length != Str.m_Length)
        return false;

    Result = memcmp(m_Data,Str.m_Data,m_Length);

    if (Result == 0)
        return true;
    
    return false;
}

std::ostream& operator << (std::ostream& os, const string& Str)
{
    short i;
    for (i=0; i < Str.m_Length-1; i ++)
        os << Str.m_Data[i];

    return os;
}

std::istream& operator >> (std::istream& is, string& Str)
{
    const short BUFLEN = 256;

    char Buf[BUFLEN];
    memset(Buf,0,BUFLEN);

    if (is.peek() == '\n')
        is.ignore();
    is.getline(Buf,BUFLEN,'\n');
    Str = Buf;

    return is;
}

