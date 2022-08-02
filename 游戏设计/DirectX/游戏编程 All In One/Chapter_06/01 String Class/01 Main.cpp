 /* '01 Main.cpp' */

 /* Input output stream header */
#include <iostream>
 /* String manipulation header */
#include <string.h>

 /* Our class */
class CString
{
private:
 char              m_aString [1024];
public:
  /* Constructors */
 CString (void);
 CString (CString & rString);
 CString (char * pString);
  /* Destructor */
 ~CString (void);

  /* Operators */
 CString & operator = (CString & rString);
 CString & operator = (char * pString);
 bool operator == (CString & rString);
 bool operator == (char * pString);
 bool operator != (CString & rString);
 bool operator != (char * pString);

  /* Other functions */
 char * GetString (void);
 int GetLength (void);
};

 /* Constructors */
CString::CString (void)
{
 m_aString [0] = '\0';
}

CString::CString (CString & rString)
{
 if (rString.GetLength () > 0)
 {
  strcpy (m_aString, rString.GetString ());
 }
 else
 {
  m_aString [0] = '\0';
 }
}

CString::CString (char * pString)
{
 if (pString)
 {
  strcpy (m_aString, pString);
 }
 else
 {
 m_aString [0] = '\0';
 }
}

 /* Destructor */
CString::~CString (void)
{
 m_aString [0] = '\0';
}

 /* Operators */
CString & CString::operator = (CString & rString)
{
 if (rString.GetLength () > 0)
 {
  strcpy (m_aString, rString.GetString ());
 }
 else
 {
 m_aString [0] = '\0';
 }

 return *this;
}

CString & CString::operator = (char * pString)
{
 if (pString)
 {
  strcpy (m_aString, pString);
 }
 else
 {
 m_aString [0] = '\0';
 }

 return *this;
}

bool CString::operator == (CString & rString)
{
 if (strcmp (rString.GetString (), m_aString) != 0)
 {
  return false;
 }
 else
 {
  return true;
 }
}

bool CString::operator == (char * pString)
{
 if (strcmp (pString, m_aString) != 0)
 {
  return false;
 }
 else
 {
  return true;
 }
}

bool CString::operator != (CString & rString)
{
 if (strcmp (rString.GetString (), m_aString) == 0)
 {
  return false;
 }
 else
 {
  return true;
 }
}

bool CString::operator != (char * pString)
{
 if (strcmp (pString, m_aString) == 0)
 {
  return false;
 }
 else
 {
  return true;
 }
}

  /* Other functions */
char * CString::GetString (void)
{
 return m_aString;
}

int CString::GetLength (void)
{
 return strlen (m_aString);
}

 /* Start */
int main ()
{
  /* Use constructor */
 CString Test ("This is just a test!");
 CString Welcome;

  /* Use assigment operator */
 Welcome = "Welcome to the world!";

  /* Use strings */
 std::cout << Welcome.GetString () << std::endl;
 std::cout << Test.GetString () << std::endl;
 std::cout << "Welcome length: " << Welcome.GetLength () << std::endl;

  /* Use comparision operator */
 if (Welcome != Test)
 {
  std::cout << "'Welcome' is different than 'Test'." << std::endl;
 }
 else
 {
  std::cout << "'Welcome' is equal to 'Test'." << std::endl;
 }

 return 0;
}