 /* '06 Main.cpp' */

 /* Input output stream header */
#include <iostream>
 /* Assertion header */
#include <assert.h>

 /* Object types */
enum ObjectTypes
{
 DogType,
 CatType
};

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
  std::cout << "Meow..." << std::endl;
  m_Age ++;
 }
}

 /* Object factory class */
class CObjectFactory
{
public:
 static CAnimal * GetType (int Type);
};

CAnimal * CObjectFactory::GetType (int Type)
{
 switch (Type)
 {
 case DogType:
  return new CDog ();
 break;
 case CatType:
  return new CCat ();
 break;

 default:
  assert (0);
 }
 return NULL;
}

 /* Start */
int main ()
{

 CAnimal * Dog;
 CAnimal * Cat;

 Dog = (CObjectFactory::GetType (DogType));
 Cat = (CObjectFactory::GetType (CatType));

 Dog->Talk ();
 Cat->Talk ();

 delete Dog;
 delete Cat;

 return 0;
}
