 /* 'mrSound.cpp' */

 /* Complement header file */
#include "mrSound.h"

 /* Default constructor */
mrSound::mrSound (void)
{
 m_lpkSound = NULL;
}

 /* Default destructor */
mrSound::~mrSound (void)
{
 if (NULL != m_lpkSound)
 {
  m_lpkSound->Release ();
  m_lpkSound = NULL;
 }
}

 /* Load the wave from file */
mrError32 mrSound::LoadFromFile (LPSTR lpszFilename)
{
 fstream     kWave;

  /* Open the wave file */
 kWave.open (lpszFilename, ios::in | ios::binary);

 if (kWave.is_open ())
 {
  mrInt8 aiID [5];
   /* Read the string RIFF identifier */
  kWave.read (aiID, sizeof (mrInt8) * 4);
  aiID [4] = '\0';
   /* If not RIFF, it is not supported */
  if (0 != strcmp (aiID, "RIFF"))
  {
   return mrErrorWaveNotSupported;
  }

  mrUInt32 iSize;
   /* Read the size of the wave */
  kWave.read ((mrInt8 *) &iSize, sizeof (mrUInt32));

   /* Read the string WAVE identifier */
  kWave.read (aiID, sizeof (mrInt8) * 4);
  aiID [4] = '\0';
   /* If not WAVE, it is not supported */
  if (0 != strcmp (aiID, "WAVE"))
  {
   return mrErrorWaveNotSupported;
  }
   /* Ignore 'fmt ' string */
  kWave.seekg (4, ios::cur);

   /* Read the 'fmt ' chunk length  */
  mrUInt32 iFormatLength;
  kWave.read ((mrInt8 *) &iFormatLength, sizeof (mrUInt32));

   /* Read the WAVEFORMATEX structure */
  WAVEFORMATEX kWaveFormat;

  kWave.read ((mrInt8 *) &kWaveFormat, sizeof (WAVEFORMATEX));
   /* Ignore two bytes since we already read the first two of
      the 'data' chunk string since WAVEFORMATEX has an extra
      two bytes */
  kWave.seekg (2, ios::cur);
  kWaveFormat.cbSize = 0;

   /* Read the size of the wave data */
  mrUInt32 iDataSize;
  kWave.read ((mrInt8 *) &iDataSize, sizeof (mrUInt32));

   /* Read the sound data */
  mrUInt8 * pkSoundBuffer = new mrUInt8 [iDataSize];
  kWave.read ((mrInt8 *) pkSoundBuffer, iDataSize);

   /* Fill DirectSound buffer description */
  DSBUFFERDESC         kBufferDesc;

  ZeroMemory (&kBufferDesc, sizeof (DSBUFFERDESC));
  kBufferDesc.dwSize        = sizeof (DSBUFFERDESC);
  kBufferDesc.dwBufferBytes = iDataSize;
  kBufferDesc.lpwfxFormat   = &kWaveFormat; 
  kBufferDesc.dwFlags       = DSBCAPS_CTRLVOLUME;
 
   /* Create the sound buffer */
  if (FAILED (mrSoundPlayer::GetSingleton()->GetSound ()->
              CreateSoundBuffer (&kBufferDesc, &m_lpkSound, NULL)) )
  {
   return mrErrorCreateSoundBuffer;
  }

   /* Lock the sound buffer */
  LPVOID lpvAudio;
  DWORD  dwBytes;
  if (FAILED (m_lpkSound->Lock(0, 0,&lpvAudio, &dwBytes, NULL, NULL, 
                               DSBLOCK_ENTIREBUFFER)) )
  {
   return mrErrorSoundBufferLock;
  }

   /* Copy the wave data to the DirectSound buffer */
  memcpy (lpvAudio, pkSoundBuffer, dwBytes);
  m_lpkSound->Unlock(lpvAudio, dwBytes, NULL, 0);

   /* Delete the memory used by the wave data and close the file */
  delete [] pkSoundBuffer;
  kWave.close ();
 }
  
 return mrNoError;
}

 /* Set the sound volume */
mrError32 mrSound::SetVolume (mrUInt32 iVolume)
{
 if (FAILED (m_lpkSound->SetVolume ((100-iVolume) * 100)) )
 {
  return mrErrorSoundSetVolume;
 }

 return mrNoError;
}

 /* Play the sound */
mrError32 mrSound::Play (mrUInt32 iLoop)
{
  /* Go to beggining of sound */
 m_lpkSound->SetCurrentPosition (0);
  /* Play sound */
 if (FAILED (m_lpkSound->Play (0, NULL, 
            (iLoop != 0) ? DSBPLAY_LOOPING : 0)) )
 {
  return mrErrorPlay;
 }
 return mrNoError;
}

 /* Stop playing the sound */
mrError32 mrSound::Stop (void)
{
 if (FAILED (m_lpkSound->Stop ()) )
 {
  return mrErrorStop;
 }
 return mrNoError;
}
