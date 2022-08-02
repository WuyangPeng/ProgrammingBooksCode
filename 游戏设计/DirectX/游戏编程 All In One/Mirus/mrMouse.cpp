 /* 'mrMouse.cpp' */

 /* Complement header file */
#include "mrMouse.h"

 /* Default constructor */
mrMouse::mrMouse (void)
{
 m_lpkDIDevice = NULL;
 ZeroMemory (&m_akDeviceData, sizeof (DIDEVICEOBJECTDATA) * 2);
}

 /* Default destructor */
mrMouse::~mrMouse (void)
{
 if (NULL != m_lpkDIDevice)
 {
  m_lpkDIDevice->Unacquire ();
  m_lpkDIDevice->Release ();
  m_lpkDIDevice = NULL;
 }
}

 /* Initializes the joystick */
mrError32 mrMouse::Init (HWND hWindow)
{
  /* Create mouse device */
 if (FAILED(mrInputManager::GetSingleton ()->GetInput ()->CreateDevice(
            GUID_SysMouse, &m_lpkDIDevice, NULL)) )
 {
  return mrErrorMouseCreateDevice;
 }

  /* Set mouse data format */
 if (FAILED (m_lpkDIDevice->SetDataFormat (&c_dfDIMouse)) )
 {
  return mrErrorMouseSetDataFormat;
 }

  /* Set mouse cooperative level */
 if (FAILED (m_lpkDIDevice->SetCooperativeLevel (hWindow, 
             DISCL_EXCLUSIVE | DISCL_FOREGROUND)) )
 {
  return mrErrorMouseSetCooperativeLevel;
 }

  /* Set buffered input (8 events) */
 DIPROPDWORD kDIProp;

 kDIProp.diph.dwSize       = sizeof(DIPROPDWORD);
 kDIProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
 kDIProp.diph.dwObj        = 0;
 kDIProp.diph.dwHow        = DIPH_DEVICE;
 kDIProp.dwData            = 8;
 
 if (FAILED (m_lpkDIDevice->SetProperty (DIPROP_BUFFERSIZE, 
                                         &kDIProp.diph)) )
 {
  return mrErrorMouseSetProperty;
 }

  /* Acquire mouse */
 m_lpkDIDevice->Acquire ();

 return mrNoError;
}

 /* Updates the mouse status */
mrError32 mrMouse::Update (void)
{
 mrUInt32 iElement;

  /* Update each element */
 for (iElement = 0; iElement < 8; iElement ++)
 {
  mrUInt32 dwElements = 1;   
 
   /* Get device data */
  HRESULT hRet = m_lpkDIDevice->GetDeviceData (
                               sizeof(DIDEVICEOBJECTDATA), 
                               &m_akDeviceData [iElement], 
                               &dwElements, 0);
  if ((FAILED (hRet)) && (hRet == DIERR_INPUTLOST))
  {
    /* Try to acquire mouse and get device data */
   m_lpkDIDevice->Acquire ();
   if (FAILED (m_lpkDIDevice->GetDeviceData (
                               sizeof(DIDEVICEOBJECTDATA), 
                               &m_akDeviceData [iElement], 
                               &dwElements, 0)) )
   {
    return mrErrorMouseGetDeviceData;
   }
  }
  else
  {
   return mrErrorMouseGetDeviceData;
  }
 }

 return mrNoError;
}
 
 /* Returns if a button is down */
mrBool32 mrMouse::IsButtonDown (mrUInt32 iButton)
{
 mrUInt32 iElements;
 mrUInt32 iMouseButton;

 switch (iButton)
 {
  case 0:
   iMouseButton = DIMOFS_BUTTON0;
  break;
  case 1:
   iMouseButton = DIMOFS_BUTTON1;
  break;
  case 2:
   iMouseButton = DIMOFS_BUTTON2;
  break;
  case 3:
   iMouseButton = DIMOFS_BUTTON3;
  break;
  default:
   iMouseButton = DIMOFS_BUTTON0;
  break;
 }

  /* Check for all states to see if button was pressed */
 for (iElements = 0; iElements < 8; iElements ++)
 {
  if ((m_akDeviceData [iElements].dwOfs == iMouseButton) || 
      (m_akDeviceData [iElements].dwData & (1<<7)))
  {
   return mrTrue;
  }
 }
 return mrFalse;
}

 /* Returns if a button is up */
mrBool32 mrMouse::IsButtonUp (mrUInt32 iButton)
{
 mrUInt32 iElements;
 mrUInt32 iMouseButton;

 switch (iButton)
 {
  case 0:
   iMouseButton = DIMOFS_BUTTON0;
  break;
  case 1:
   iMouseButton = DIMOFS_BUTTON1;
  break;
  case 2:
   iMouseButton = DIMOFS_BUTTON2;
  break;
  case 3:
   iMouseButton = DIMOFS_BUTTON3;
  break;
  default:
   iMouseButton = DIMOFS_BUTTON0;
  break;
 }
  
  /* Check for all states to see if button was released */
 for (iElements = 0; iElements < 8; iElements ++)
 {
  if ((m_akDeviceData [iElements].dwOfs == iMouseButton) || 
     !(m_akDeviceData [iElements].dwData & (1<<7)))
  {
   return mrTrue;
  }
 }
 return mrFalse;
}

 /* Returns mouse horizontal axis */
mrUInt32 mrMouse::GetXAxis (void)
{
 mrUInt32 iElements;
 mrUInt32 iMovement;

 iMovement = 0;
  
  /* Sum all the relative X movement of the mouse in the last events */
 for (iElements = 0; iElements < 8; iElements ++)
 {
  if (DIMOFS_X == m_akDeviceData [iElements].dwOfs)
  {
   iMovement += m_akDeviceData [iElements].dwData;
  }
 }
 return iMovement;
}

 /* Returns mouse vertical axis */
mrUInt32 mrMouse::GetYAxis (void)
{
 mrUInt32 iElements;
 mrUInt32 iMovement;

 iMovement = 0;
  
  /* Sum all the relative Y movement of the mouse in the last events */
 for (iElements = 0; iElements < 8; iElements ++)
 {
  if (DIMOFS_Y == m_akDeviceData [iElements].dwOfs)
  {
   iMovement += m_akDeviceData [iElements].dwData;
  }
 }
 return iMovement;
}

 /* Clears the mouse buffer */
mrError32 mrMouse::Clear (void)
{
  /* Clear device buffer */
 ZeroMemory (m_akDeviceData, sizeof (DIDEVICEOBJECTDATA) * 8);

 mrUInt32 dwItems = INFINITE; 
 if (FAILED (m_lpkDIDevice->GetDeviceData (sizeof(DIDEVICEOBJECTDATA),
                                           NULL, &dwItems, 0)) )
 {
  return mrErrorMouseGetDeviceData;
 }

 return mrNoError;
}
