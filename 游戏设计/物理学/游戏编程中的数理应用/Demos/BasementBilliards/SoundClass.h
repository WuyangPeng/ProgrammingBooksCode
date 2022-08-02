#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_

#include <dsound.h>

typedef short  SampleHandle;

// class SoundClass : loads/manages/plays wav sounds
//
class SoundClass 
{
public:
	enum { MAX_SOUNDS = 128 };
	// primary buffer quality constants
	enum { PB_LOQUAL = 1, PB_MEDQUAL, PB_HIQUAL };
private:

	// SoundDevice main variables
	LPDIRECTSOUND  soundInterface;
	HWND           main_window_handle;
	int            soundsLoaded;

	// Sgd_Sound struct contains data on the loaded sound files
	struct Sound 
	{
		char                 filename[ 128 ];
		unsigned char        max_overplay;
		WAVEFORMATEX         format;
		LPDIRECTSOUNDBUFFER  buffer;

	} sounds[MAX_SOUNDS];

	// findSample : searches the cache for previous instance of a sound
	SampleHandle findSample( char* filename, int &openIndex );

	// loads the data into the struct from a file
	int loadSampleData( char *filename, Sound &snd );

public:

	SoundClass();
	~SoundClass();

	// init : Init routine for DirectSound setup
	int init ( HWND hwnd, int primaryBufferFormat = PB_LOQUAL );

	// shutdown : shutdown routine for DirectSound
	void shutdown ();

	// loadSample : loading routine for DirectSound samples (Reads a RIFF/WAV format)
	SampleHandle loadSample( char *filename );

	// unloadSample : free's allocated information to the associated sound
	int unloadSample( SampleHandle sampleID );

	// playSample : play the sound with the given sampleID
	int playSample( SampleHandle sampleID, DWORD flags = 0, bool playFromBeginning = true );

	// resetSample : sets the position of sample playback back to the beginning
	int resetSample( SampleHandle sampleID );

	// stopSample : stop the playing sound with the given sampleID
	int stopSample( SampleHandle sampleID );

	// isSamplePlaying : checks to see if a sample is currently playing
	bool isSamplePlaying (SampleHandle sampleID);

	void setSampleVolume( SampleHandle sampleID, int volume ); 
};

#endif