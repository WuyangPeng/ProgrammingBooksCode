 /* 'mrSoundPlayer.cpp' */

 /* Complement header file */
#include "mrSoundPlayer.h"

 /* Singleton object */
mrSoundPlayer * mrSoundPlayer::m_pkSingleton = NULL;

 /* Default constructor */
mrSoundPlayer::mrSoundPlayer (void)
{
 m_lpkDSound = NULL;

 assert (!m_pkSingleton);
 m_pkSingleton = this;
}

 /* Default destructor */
mrSoundPlayer::~mrSoundPlayer (void)
{
 if (NULL != m_lpkDSound)
 {
  m_lpkDSound->Release ();
  m_lpkDSound = NULL;
 }

 assert (m_pkSingleton);
 m_pkSingleton = NULL;
}

 /* Initializes the sound player */
mrError32 mrSoundPlayer::Init (HWND hWindow)
{
  /* Create DirectSound object */
 DirectSoundCreate8 (NULL, &m_lpkDSound, NULL);

 if (NULL == m_lpkDSound)
 {
  return mrErrorCreateSoundDevice;
 }

  /* Set DirectSound cooperative level */
 if (FAILED (m_lpkDSound->SetCooperativeLevel (hWindow, DSSCL_NORMAL)) )
 {
  return mrErrorSetCooperativeLevel;
 }
 return mrNoError;
}

 /* Returns a pointer to the DirectSound interface */
LPDIRECTSOUND8 mrSoundPlayer::GetSound (void)
{
 return m_lpkDSound;
}

 /* Returns the mrSoundPlayer singleton */
mrSoundPlayer * mrSoundPlayer::GetSingleton (void)
{
 assert (m_pkSingleton);
 return m_pkSingleton;
}
