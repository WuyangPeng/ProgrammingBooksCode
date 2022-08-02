 /* 'mrInputManager.cpp' */

 /* Complement header file */
#include "mrInputManager.h"

 /* Singleton object */
mrInputManager * mrInputManager::m_pkSingleton = NULL;

 /* Default constructor */
mrInputManager::mrInputManager (void)
{
 m_lpkDInput = NULL;

 assert (!m_pkSingleton);
 m_pkSingleton = this;
}

 /* Default destructor */
mrInputManager::~mrInputManager (void)
{
 if (NULL != m_lpkDInput)
 {
  m_lpkDInput->Release ();
  m_lpkDInput = NULL;
 }

 assert (m_pkSingleton);
 m_pkSingleton = NULL;
}

 /* Initializes the input manager */
mrError32 mrInputManager::Init (HINSTANCE hInstance)
{
  /* Create Direct Input object */
 if (FAILED (DirectInput8Create (hInstance, DIRECTINPUT_VERSION, 
                                 IID_IDirectInput8, 
                                 (void**) &m_lpkDInput, NULL)))
 {
  return mrErrorDInputCreate;
 }
 return mrNoError;
}

 /* Returns a pointer to the DirectInput interface */
LPDIRECTINPUT8 mrInputManager::GetInput (void)
{
 return m_lpkDInput;
}

 /* Returns the mrInputManager singleton */
mrInputManager * mrInputManager::GetSingleton (void)
{
 assert (m_pkSingleton);
 return m_pkSingleton;
}