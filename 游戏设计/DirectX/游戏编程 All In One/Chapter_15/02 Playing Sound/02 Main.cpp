 /* '02 Main.cpp' */

 /* Mirus header */
#include "mirus.h"

 /* Sound class */
class SoundWindow : public mrWindow
{
  /* Sound classes */
 mrSoundPlayer   m_kSoundPlayer;
 mrSound         m_kSound;
 mrCDPlayer      m_kCDPlayer;

public:
  /* Constructor / Destructor */
 SoundWindow (void);
 ~SoundWindow (void);

 void Init (HINSTANCE hInstance);

  /* Window manipulation functions */
 mrBool32 Frame (void);
};

SoundWindow::SoundWindow (void)
{
}

SoundWindow::~SoundWindow (void)
{
  /* Stop playback */
 m_kSound.Stop ();
 m_kCDPlayer.Stop ();
}

void SoundWindow::Init (HINSTANCE hInstance)
{
   /* Initialize DirectSound */
 m_kSoundPlayer.Init (m_hWindow);
  /* Load the files from the disk */
 m_kSound.LoadFromFile ("Sound.wav");
 m_kSound.Play (mrTrue);
  /* Play CD */
 m_kCDPlayer.Update ();
 m_kCDPlayer.Play (1);
}

 /* Render frame */
mrBool32 SoundWindow::Frame(void)
{
 return mrTrue;
}

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  /* Our window */
 SoundWindow  kWindow;

  /* Create window */
 kWindow.Create (hInstance, "Sound Test");
 kWindow.SetSize (640, 480);
 
 kWindow.Init (hInstance);
 kWindow.Run ();

 return 0;
}
