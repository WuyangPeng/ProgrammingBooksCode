 /* 'mrCDPlayer.cpp' */

 /* Complement header file */
#include "mrCDPlayer.h"

 /* Default constructor */
mrCDPlayer::mrCDPlayer (void)
{
  /* Open the cd device */
 mciSendString ("open cdaudio", NULL, 0, NULL);
}

 /* Default destructor */
mrCDPlayer::~mrCDPlayer (void)
{
  /* Stop playing */
 Stop ();
  /* Close the cd device */
 mciSendString ("close cdaudio", NULL, 0, NULL);
}

 /* Eject the current CD */
void mrCDPlayer::Eject (void)
{
 mciSendString ("set cdaudio door open", NULL, 0, NULL);
}

 /* Play a track */
void mrCDPlayer::Play (mrUInt32 iTrack)
{
 mrInt8 szSendString [256];

  /* Play from iTrack to the final track */
 sprintf (szSendString, "play cdaudio from %d to %d", iTrack, m_iNumberTracks);
 mciSendString (szSendString, NULL, 0, NULL);
}

 /* Stop playing */
void mrCDPlayer::Stop (void)
{
 mciSendString ("stop cdaudio", NULL, 0, NULL);
}

 /* Update CD information */
void mrCDPlayer::Update (void)
{
 mrInt8 szReturnString [256];

  /* Get number of tracks */
 mciSendString ("status cdaudio number of tracks", szReturnString, 255, NULL);
 m_iNumberTracks = atoi (szReturnString);

  /* Get CD length */
 mciSendString ("status cdaudio length", m_szLength, 255, NULL);
}

 /* Returns the number of tracks of the CD */
mrUInt32 mrCDPlayer::GetNumberOfTracks (void)
{
 return m_iNumberTracks;
}

 /* Returns the length of the CD */
mrInt8 * mrCDPlayer::GetLength (void)
{
 return m_szLength;
}

 /* Returns the current track of the CD */
mrUInt32 mrCDPlayer::GetCurrentTrack (void)
{
 return m_iCurrentTrack;
}

 /* Returns if the CD is ready to be used */
mrBool32 mrCDPlayer::IsReady (void)
{
 mrInt8 szReturnString [256];

 mciSendString ("status cdaudio ready", szReturnString, 255, NULL);

 if (0 == strcmp (szReturnString, "true") )
 {
  return mrTrue;
 }
 else
 {
  return mrFalse;
 }
}