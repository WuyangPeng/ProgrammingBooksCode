 /* 'mrKeyboard.cpp' */

 /* Complement header file */
#include "mrKeyboard.h"

 /* Default constructor */
mrKeyboard::mrKeyboard (void)
{
 m_lpkDIDevice = NULL;
 ZeroMemory (m_iKeyBuffer, sizeof (mrUInt8) * 256);
}

 /* Default destructor */
mrKeyboard::~mrKeyboard (void)
{
 if (NULL != m_lpkDIDevice)
 {
  m_lpkDIDevice->Unacquire ();
  m_lpkDIDevice->Release ();
  m_lpkDIDevice = NULL;
 }
}

 /* Initializes the keyboard */
mrError32 mrKeyboard::Init (HWND hWindow)
{
  /* Create keyboard device */
 if (FAILED(mrInputManager::GetSingleton ()->GetInput ()->CreateDevice(
            GUID_SysKeyboard, &m_lpkDIDevice, NULL)) )
 {
  return mrErrorKeyboardCreateDevice;
 }

  /* Set keyboard data format */
 if (FAILED (m_lpkDIDevice->SetDataFormat (&c_dfDIKeyboard)) )
 {
  return mrErrorKeyboardSetDataFormat;
 }

  /* Set keyboard cooperative level */
 if (FAILED (m_lpkDIDevice->SetCooperativeLevel (hWindow, 
             DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)) )
 {
  return mrErrorKeyboardSetCooperativeLevel;
 }

  /* Acquire keyboard */
 m_lpkDIDevice->Acquire ();

 return mrNoError;
}

 /* Updates the keyboard status */
mrError32 mrKeyboard::Update (void)
{
  /* Get device data */
 HRESULT hRet = m_lpkDIDevice->GetDeviceState (sizeof (mrUInt8) * 256,
                                               (LPVOID) &m_iKeyBuffer);
 
 if (hRet == DIERR_INPUTLOST)
 {
    /* Try to acquire keyboard */
  if (FAILED (m_lpkDIDevice->Acquire ()) )
  { 
   return mrErrorKeyboardAcquire; 
  } 
 }
 if (FAILED (hRet))
	{
		return mrErrorKeyboardGetDeviceData; 
	}
 return mrNoError;
}

 /* Returns if a button is down */
mrBool32 mrKeyboard::IsButtonDown (mrUInt32 iButton)
{
  /* Check if button is pressed */
 if (m_iKeyBuffer [iButton] & (1<<7))
 {
  return mrTrue;
 }
 else
 {
  return mrFalse;
 }
}

 /* Returns if a button is up */
mrBool32 mrKeyboard::IsButtonUp (mrUInt32 iButton)
{
  /* Check if button isn't pressed */
 if (!(m_iKeyBuffer [iButton] & (1<<7)))
 {
  return mrTrue;
 }
 else
 {
  return mrFalse;
 }
}
