#include <cstring>
using std::memcpy;
using std::strlen;

#include "string1.h"

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
