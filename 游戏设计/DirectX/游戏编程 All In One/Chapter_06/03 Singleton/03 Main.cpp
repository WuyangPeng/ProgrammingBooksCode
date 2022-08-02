 /* '03 Main.cpp' */

 /* Input output stream header */
#include <iostream>
 /* Assertion header */
#include <assert.h>

 /* Singleton class */
class CSingletonExample
{
private:
 static CSingletonExample * m_Singleton;

public:

 CSingletonExample ();
 virtual ~CSingletonExample ();

 static CSingletonExample * GetSingleton (void);
};

CSingletonExample * CSingletonExample::m_Singleton;


CSingletonExample::CSingletonExample ()
{
 assert (!m_Singleton);

 m_Singleton = this;
}

CSingletonExample::~CSingletonExample ()
{
 assert (m_Singleton);

 m_Singleton = NULL;
}

CSingletonExample * CSingletonExample::GetSingleton ()
{
 assert (m_Singleton);

 return m_Singleton;
}