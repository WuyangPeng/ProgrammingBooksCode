 /* '02 Main.cpp' */

 /* Input output stream header */
#include <iostream>

 /* Base animal class */
class CAnimal
{
public:
 int   m_MaxAge;
 int   m_Age;

 CAnimal ();
 virtual ~CAnimal ();

 virtual void Talk (void);
};

CAnimal::CAnimal ()
{
 m_MaxAge = 0;
 m_Age    = 0;
}

CAnimal::~CAnimal ()
{
}

void CAnimal::Talk (void)
{
 std::cout << "Base animal doesn't talk!";
}

 /* Derived dog class */
class CDog : public CAnimal
{
public:
 CDog ();
 virtual ~CDog ();

 virtual void Talk (void);
};

CDog::CDog ()
{
 m_MaxAge = 9;
 m_Age    = 0;
}

CDog::~CDog ()
{
}

void CDog::Talk (void)
{
 if (m_Age < m_MaxAge)
 {
  std::cout << "Bark..." << std::endl;
  m_Age ++;
 }
}

 /* Derived cat class */
class CCat : public CAnimal
{
public:
 CCat ();
 virtual ~CCat ();

 virtual void Talk (void);
};

CCat::CCat ()
{
 m_MaxAge = 5;
 m_Age    = 0;
}

CCat::~CCat ()
{
}

void CCat::Talk (void)
{
 if (m_Age < m_MaxAge)
 {
  std::cout << "MEOW..." << std::endl;
  m_Age ++;
 }
}

 /* Start */
int main ()
{
 CDog Dog;
 CCat Cat;
 int Loop;

 for (Loop = 0; Loop < 10; Loop ++)
 {
  Dog.Talk ();
  Cat.Talk ();
 }

 return 0;
}



