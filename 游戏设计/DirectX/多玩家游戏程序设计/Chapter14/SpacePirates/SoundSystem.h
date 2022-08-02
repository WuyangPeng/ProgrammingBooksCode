#include <dmusici.h>
#include <dsound.h>
#include <dshow.h>

#define SOUNDERROR_MUSICLOADER		0x85000001
#define SOUNDERROR_MUSICPERFORMANCE	0x85000002
#define SOUNDERROR_INITAUDIO		0x85000003
#define SOUNDERROR_PATH				0x85000004
#define SOUNDERROR_VOLUME			0x85000005
#define SOUNDERROR_LOAD				0x85000006
#define SOUNDERROR_DOWNLOAD			0x85000007
#define SOUNDERROR_NOSEGMENT		0x85000008
#define SOUNDERROR_PLAYFAIL			0x85000009

class GameSound
{
	public:
		IDirectMusicSegment8		*pSound;
		IDirectMusicPerformance8	*pPerformance;
		~GameSound();
		GameSound();
};

class SoundSystem
{
	private:	

	public:
		HWND						hWnd;
		//
		// Sound System
		//
		IDirectMusicLoader8			*pLoader;
		IDirectMusicPerformance8	*pPerformance;
		
		// Functions
		SoundSystem();
		~SoundSystem();
		HRESULT	hrInitSoundSystem(void);
		HRESULT hrLoadSound(char *szname,GameSound *gs);
		HRESULT hrPlaySound(GameSound *gs);
};

