 /* 'mrJoystick.cpp' */

 /* Complement header file */
#include "mrJoystick.h"

 /* Enumeration function */
BOOL CALLBACK EnumJoysticksCallback(
          const DIDEVICEINSTANCE *pdidInstance, VOID* pContext)
{
 LPDIRECTINPUTDEVICE8 * lpkDevice = (LPDIRECTINPUTDEVICE8 *) pContext;
 
  /* Create joystick device */
 if (FAILED(mrInputManager::GetSingleton ()->GetInput ()->CreateDevice (
             pdidInstance->guidInstance, lpkDevice, NULL)) )
 {
  return DIENUM_CONTINUE;
 }
 else
 {
  return DIENUM_STOP;
 }
}

 /* Default constructor */
mrJoystick::mrJoystick (void)
{
 m_lpkDIDevice = NULL;
 ZeroMemory (&m_kDeviceData, sizeof (DIDEVICEOBJECTDATA));
}

 /* Default destructor */
mrJoystick::~mrJoystick (void)
{
 if (NULL != m_lpkDIDevice)
 {
  m_lpkDIDevice->Unacquire ();
  m_lpkDIDevice->Release ();
  m_lpkDIDevice = NULL;
 }
}

 /* Initializes the joystick */
mrError32 mrJoystick::Init (HWND hWindow, mrInt32 iMin, mrInt32 iMax,
                            mrInt32 iDeadZone)
{
  /* Find first available joystick */
 if (FAILED (mrInputManager::GetSingleton ()->GetInput ()->EnumDevices (
             DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &m_lpkDIDevice, 
             DIEDFL_ATTACHEDONLY)) )
 {
  return mrErrorJoystickEnumDevices;
 }
 
  /* Set joystick data format */
 if (FAILED(m_lpkDIDevice->SetDataFormat (&c_dfDIJoystick2)))
 {
  return mrErrorJoystickSetDataFormat;
 }
 
  /* Set joystick cooperative level */
 if (FAILED(m_lpkDIDevice->SetCooperativeLevel (hWindow, 
            DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
 {
  return mrErrorJoystickSetCooperativeLevel;
 }
 
  /* Set joystick axis ranges */
 DIPROPRANGE kDIRange; 
 
 kDIRange.diph.dwSize       = sizeof(DIPROPRANGE); 
 kDIRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
 kDIRange.diph.dwHow        = 0; 
 kDIRange.diph.dwObj        = DIPH_DEVICE; 
 kDIRange.lMin              = iMin; 
 kDIRange.lMax              = iMax; 
 
 if (FAILED(m_lpkDIDevice->SetProperty (DIPROP_RANGE, &kDIRange.diph)))
 {
  return mrErrorJoystickSetProperty;
 }

  /* Set joystick dead zone */
 DIPROPDWORD kDIDeadZone; 
 
 kDIDeadZone.diph.dwSize       = sizeof(DIPROPDWORD); 
 kDIDeadZone.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
 kDIDeadZone.diph.dwHow        = 0; 
 kDIDeadZone.diph.dwObj        = DIPH_DEVICE; 
 kDIDeadZone.dwData            = iDeadZone * 100; 
 
 if (FAILED (m_lpkDIDevice->SetProperty (DIPROP_DEADZONE,
                                         &kDIDeadZone.diph)) )
 {
  return mrErrorJoystickSetProperty;
 }
 
  /* Acquire joystick */
 HRESULT hRet = m_lpkDIDevice->Poll (); 
 if (FAILED (hRet)) 
 {
  hRet = m_lpkDIDevice->Acquire ();
  
  while (hRet == DIERR_INPUTLOST) 
  {
   hRet = m_lpkDIDevice->Acquire ();
  }
 }
 return mrNoError;
}

 /* Update joystick status */
mrError32 mrJoystick::Update (void)
{
  /* Poll the joystick */
 if (FAILED (m_lpkDIDevice->Poll ()) )  
 {
   /* Acquire joystick */
  HRESULT hRet = m_lpkDIDevice->Acquire ();

  if ((FAILED (hRet)) && (hRet == DIERR_INPUTLOST))
  {
   m_lpkDIDevice->Acquire ();
  }
  else
  {
   return mrErrorJoystickAcquire;
  }
 }
 
  /* Get device data */
 if (FAILED (m_lpkDIDevice->GetDeviceState (sizeof (DIJOYSTATE2),
                                            &m_kDeviceData)) )
 {
  return mrErrorJoystickGetDeviceState;
 }
 return mrNoError; 
}

 /* Returns if a button is down */
mrBool32 mrJoystick::IsButtonDown (mrUInt32 iButton)
{
  /* Check if button is pressed */
 if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
 {
  return mrTrue;
 }
 else
 {
  return mrFalse;
 }
}

 /* Returns if a button is up */
mrBool32 mrJoystick::IsButtonUp (mrUInt32 iButton)
{
  /* Check if button isn't pressed */
 if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
 {
  return mrFalse;
 }
 else
 {
  return mrTrue;
 }
}

 /* Returns joystick horizontal axis */
mrUInt32 mrJoystick::GetXAxis (void)
{
 return m_kDeviceData.lX;
}
 
 /* Returns joystick vertical axis */
mrUInt32 mrJoystick::GetYAxis (void)
{
 return m_kDeviceData.lY;
}
