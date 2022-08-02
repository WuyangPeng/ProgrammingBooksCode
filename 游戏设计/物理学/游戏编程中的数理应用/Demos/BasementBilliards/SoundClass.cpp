#include "SoundClass.h"
#include <stdio.h>

// SoundClass : constructor for SoundDevice manager class
SoundClass::SoundClass() 
{
   // clear all values in the sound array
   soundInterface = NULL;
   soundsLoaded = 0;
   for( int i = 0; i < MAX_SOUNDS; i++)
   {
      strcpy(sounds[i].filename, "");
      sounds[i].buffer = NULL;
      memset(&sounds[i].format, 0, sizeof( sounds[i].format ) );
   }
   return;
}

// ~SoundClass : destructor for SoundDevice manager class
SoundClass::~SoundClass() 
{
	shutdown();
   return;
}

// init : Init routine for DirectSound setup
int SoundClass::init( HWND windowHandle, int primaryBufferFormat ) 
{
   // already initialized 
   if( soundInterface != NULL)
   {
      MessageBox(windowHandle, "Couldn't Initialize - Sound System Already Initialized", "DirectSound Error", MB_OK);
      return 0; 
   }

   // setup the sound manager 
   if( DirectSoundCreate( NULL, &soundInterface, NULL) != DS_OK ) 
   {
      MessageBox(windowHandle, "Couldn't Initialize - Sound System in Use", "DirectSound Error", MB_OK);
      return 0;
   }

   // set the level of interaction for windows 
   if (primaryBufferFormat != PB_MEDQUAL && primaryBufferFormat != PB_HIQUAL) // default
   {
      soundInterface ->SetCooperativeLevel(windowHandle, DSSCL_NORMAL);
   }
   else
   {
      // attempt to set the primary buffer format
      // we're doing this because DirectSound likes to convert our samples to its
      // default low qual format, causing lots of white noise on our samples
      if (soundInterface ->SetCooperativeLevel(windowHandle, DSSCL_PRIORITY) != DS_OK)
      {
         MessageBox(windowHandle, "Couldn't Set Priority Access to DS", "DirectSound Error", MB_OK);
         return 0;
      }

      // make a wave format structure for our primary sound buffer
      WAVEFORMATEX wf;
      DSBUFFERDESC dsbdesc;
      LPDIRECTSOUNDBUFFER lpDsb;
      memset(&wf, 0, sizeof(WAVEFORMATEX));
      wf.wFormatTag = WAVE_FORMAT_PCM;
      wf.nChannels = 2;
      // give us 22050 or 44100
      (primaryBufferFormat == PB_MEDQUAL) ? wf.nSamplesPerSec = 22050 : wf.nSamplesPerSec = 44100;
      wf.nBlockAlign = 4;
      wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
      wf.wBitsPerSample = 16;
      // Set up DSBUFFERDESC structure.
      memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
      dsbdesc.dwSize = sizeof(DSBUFFERDESC);
      dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
      dsbdesc.dwBufferBytes = 0;
      dsbdesc.lpwfxFormat = NULL; // Must be NULL for primary buffers.

      // make the primary sound buffer
      if (soundInterface->CreateSoundBuffer(&dsbdesc, &lpDsb, NULL) != DS_OK)
      {
         MessageBox(windowHandle, "Couldn't Create the Primary Sound Buffer", "DirectSound Error", MB_OK);
         return 0;
      }

      // set the desired format for the buffer
      if (lpDsb->SetFormat(&wf) != DS_OK)
      {
         MessageBox(windowHandle, "Couldn't Set the Primary Sound Buffer Format", "DirectSound Error", MB_OK);
         return 0;
      }
   }

   main_window_handle = windowHandle;
   return 1;
}

// shutdown : shut-down routine for DirectSound
void SoundClass::shutdown() 
{
   // delete all the sound buffers we have loaded
   for( int i = 0; i < soundsLoaded; i++)
      unloadSample( i );
   soundsLoaded = 0;

   // release the interface com object
   if( soundInterface ) 
   {
      soundInterface ->Release();
      soundInterface = NULL;
   }
   return;
}

// loadSample : loading routine for DirectSound samples (Reads a RIFF/WAV format)
SampleHandle SoundClass::loadSample( char *filename )
{
   // try to get a cached copy
   int openIndex = 0;
   SampleHandle id = findSample(filename, openIndex);
   if( id >= 0 ) return id;

   // load a new copy of it into the first open index
   if( openIndex < MAX_SOUNDS )
   {
      if( loadSampleData(filename, sounds[openIndex] ) )
      {
         if (openIndex == soundsLoaded)
            return soundsLoaded++;
         else
            return openIndex;
      }
   }

   return -1;
}

// loads the data into the struct from a file
int SoundClass::loadSampleData( char *filename, Sound &snd )
{
   DSBUFFERDESC  desc;
   WAVEFORMATEX  format;
   FILE*         fp;
   char          scratch[25];
   int           sample_size;
   int           length;
   unsigned char *pdata = NULL,    // temporary sound buffer to hold voc data
      *audio_ptr_1 = NULL,         // data ptr to first write buffer 
	   *audio_ptr_2 = NULL;         // data ptr to second write buffer
   unsigned long  audio_length_1,  // length of first write buffer
                  audio_length_2;  // length of second write buffer

   // check to see if we have been initialized
   if( !soundInterface ) { return 0; }

   // open the file
   fp = fopen( filename, "rb");
   if( !fp ) 
   {
      MessageBox(main_window_handle, "Could Not Open File..", "Sound Loading Error", MB_OK);
      return 0;
   }

   // check RIFF header
   fread(scratch, 12, 1, fp );
   if (memcmp(scratch, "RIFF", 4) || memcmp(scratch+8, "WAVE", 4)) 
   {
      MessageBox(main_window_handle, scratch, "Invalid WAV Format", MB_OK);
      fclose( fp );
      return 0;
   }

   // read all the wav info
   while( !feof( fp ) ) 
   {
      if( fread(scratch, 4, 1, fp) == 0 ) 
			break;

      // search for the "format" of the wav file
      if (memcmp(scratch, "fmt ", 4) == 0) 
      {
         fread( &format.cbSize, sizeof( int ), 1, fp );
         fread( &format.wFormatTag, sizeof( short ), 1, fp );
         fread( &format.nChannels, sizeof( short ), 1, fp );
         fread( &format.nSamplesPerSec, sizeof( int ), 1, fp );
         fread( &format.nAvgBytesPerSec, sizeof( int ), 1, fp );
         fread( &format.nBlockAlign, sizeof( short ), 1, fp );
         fread( &format.wBitsPerSample, sizeof( short ), 1, fp );

         // check to see if we support the wav type 
         if( format.wFormatTag != WAVE_FORMAT_PCM ) 
         {
            MessageBox(main_window_handle, "Invalid PCM Information...", "WAV Error", MB_OK);
            fclose( fp );
            return 0;
         }

         // make sure this is a valid format
         if ((format.wBitsPerSample != 8) && (format.wBitsPerSample != 16)) 
         {
            MessageBox(main_window_handle, "Invalid Bits Per Sample...", "WAV error", MB_OK);
            fclose( fp );
            return 0;
         }

         // parse through junk
         fread(scratch, 4, 1, fp);
         while( memcmp(scratch, "data", 4) != 0 ) 
         {
            // shift data up
            memcpy(scratch, scratch + 1, 3);

            // read next byte
            scratch[3] = fgetc( fp );
            if( feof( fp ) ) 
            {
               // check for corrupt or early ending file
               // could not find the "data" of the wav file
               break;
            }
         }
         // we found the "data" of the wav file.. move back to let the main loop handle
         // the loading.
         fseek(fp, -4, SEEK_CUR);

         // just in case
         length = 0;
      }
      else if (memcmp(scratch, "data", 4) == 0) 
      {
         // read chunk length
         fread(&length, 4, 1, fp);

         // create surface pointer
         pdata = new unsigned char[ length ];
         sample_size = length;

         // set up the sound buffer
         if ( pdata) 
         {
            // the data into the sound buffer
            fread(pdata, length, 1, fp);

            // reset since all the data has been use
            length = 0;

            // check for pre-mature ending of file
            if( feof( fp ) ) 
            {
               delete [] pdata;
               fclose( fp );
               return 0;
            }
         }
         else 
         {
            // the memory buffer was not allocated!!
            MessageBox(main_window_handle,  "Could Not Create Sound Buffer...", "WAV Error", MB_OK);
            fclose( fp );
            return 0;
         }
      }

      // skip the remainder of the chunk
      while (length > 0) 
      {
         if( fgetc( fp ) == EOF )
            break;
         length--;
      }
   }

   // close the file
   fclose( fp );

   // create the surface and attach sound data
   memset( &desc, 0, sizeof( desc ) );
   desc.dwSize = sizeof( desc );
   desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | 
                  DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
   desc.dwBufferBytes = sample_size;
   desc.lpwfxFormat = &format;
   
   // initialize the cache for the new element
   strcpy(snd.filename, filename);
   snd.max_overplay = 0;
   snd.format = format;
   snd.format.cbSize = 0;
   if( soundInterface ->CreateSoundBuffer( &desc, &snd.buffer, NULL) != DS_OK) 
   {
      delete [] pdata;
      return 0;
   }

   if(snd.buffer ->Lock(0,					 
                           sample_size,			
                           (void **) &audio_ptr_1, 
                           &audio_length_1,
                           (void **)&audio_ptr_2, 
                           &audio_length_2,
                           DSBLOCK_FROMWRITECURSOR ) != DS_OK) 
   {
      return 0;
   }

   // copy first section of circular buffer
   memcpy(audio_ptr_1, pdata, audio_length_1);

   // copy last section of circular buffer
   memcpy(audio_ptr_2, (pdata + audio_length_1), audio_length_2);

   // unlock the buffer
   if (snd.buffer ->Unlock(audio_ptr_1, 
                                 audio_length_1, 
                                 audio_ptr_2, 
                                 audio_length_2) != DS_OK) 
   {
      return 0;
   }

   // release the temp buffer
	delete [] pdata;

   return 1;
}


// findSample : searches the cache for previous instance of a sound
SampleHandle SoundClass::findSample( char* filename, int &openIndex ) 
{
   openIndex = -1;
   // return the previous instance if the sound was already loaded
   for( int i = 0; i < soundsLoaded; i++) 
   {
      if ((!(sounds[i].buffer)) && openIndex == -1)
         openIndex = i; // store the first open index
      if( sounds[i].buffer && strcmp(sounds[i].filename, filename) == 0) 
         return i;
   }

   // couldn't find the sound
   if (openIndex == -1) openIndex = soundsLoaded;
   return -1;
}


// unloadSample : free's allocated information to the associated sound
int SoundClass::unloadSample( SampleHandle sampleID ) 
{
   // kill the sample then release all its info
   if( stopSample( sampleID ) ) 
   {
      sounds[sampleID].buffer ->Release();
      sounds[sampleID].buffer = NULL;
      strcpy(sounds[sampleID].filename, "");
      memset(&sounds[sampleID].format, 0, sizeof( sounds[sampleID].format ) );
      return 1;
   }
   return 0;
}


// playSample : play the sound with the given sampleID
int SoundClass::playSample( SampleHandle sampleID, DWORD flags, bool playFromBeginning)
{
   // error check and make sure the system has been initialized
   if( !soundInterface ) { return 0; } 

   // check the bounding of the sound array
   if(sampleID < 0 || sampleID >= soundsLoaded  || !sounds[sampleID].buffer) 
      return 0;

   // check our sound status flags
   DWORD status = 0;
   if( sounds[sampleID].buffer ->GetStatus(&status) != DS_OK )
      return 0;

   // if we want to play from beginning....
   if (playFromBeginning)
   {
      // simply reset our sound to the beginning
      if (sounds[sampleID].buffer ->SetCurrentPosition (0) != DS_OK)
         return 0;

      // check to see if we're not already playing
      if (!( status & DSBSTATUS_PLAYING || status & DSBSTATUS_LOOPING ))
      {
         // play sound
         if ( sounds[sampleID].buffer ->Play(0,0,flags) != DS_OK )
            return 0;
      }
   }
   else
   {
      // only play if the sound isn't already playing,
      // and don't bother resetting position
      // check to see if we're not already playing
      if (!( status & DSBSTATUS_PLAYING || status & DSBSTATUS_LOOPING ))
      {
         // play sound
         if ( sounds[sampleID].buffer ->Play(0,0,flags) != DS_OK )
            return 0;
      }
   }

   // success
   return 1;
}

// stopSample : stop the playing sound with the given sampleID
int SoundClass::stopSample( SampleHandle sampleID ) 
{
   if( !soundInterface ) { return 0; } 

   // check the bounding of the sound array
   if(sampleID < 0 || sampleID >= soundsLoaded  || !sounds[sampleID].buffer) 
      return 0;

   // stop the sound from playing
   if ( sounds[sampleID].buffer ->Stop() != DS_OK)
      return 0;

   // successfully stopped the sound
   return 1;
}

// resetSample : sets the position of sample playback
int SoundClass::resetSample( SampleHandle sampleID )
{
   if( !soundInterface ) { return 0; } 

   // check the bounding of the sound array
   if(sampleID < 0 || sampleID >= soundsLoaded  || !sounds[sampleID].buffer) 
      return 0;

   // reset the playing position of the sample
   if (sounds[sampleID].buffer ->SetCurrentPosition (0) != DS_OK)
      return 0;

   // successfully stopped the sound
   return 1;
}

// isSamplePlaying : checks to see if a sample is currently playing
bool SoundClass::isSamplePlaying (SampleHandle sampleID)
{
   if( !soundInterface ) { return false; } 

   // check the bounding of the sound array
   if(sampleID < 0 || sampleID >= soundsLoaded  || !sounds[sampleID].buffer) 
      return false;

   // check our sound status
   DWORD status = 0;
   if( sounds[sampleID].buffer ->GetStatus(&status) != DS_OK )
      return 0;

   if (status & DSBSTATUS_PLAYING || status & DSBSTATUS_LOOPING)
      return true;

   return false;
}
// setSampleVolume : sets the volume ranging [0, 100]
void SoundClass::setSampleVolume( SampleHandle sampleID, int volume ) 
{
   if( !soundInterface ) { return; } 

   // check the bounding of the sound array
   if(sampleID < 0 || sampleID >= soundsLoaded  || !sounds[sampleID].buffer) 
      return;

   // limit the bounds of our volume
   if(volume < 0)    { volume = 0; }
   if(volume > 100)  { volume = 100; }

   volume = -30 * (100 - volume);
   sounds[sampleID].buffer ->SetVolume( volume );
   return;
}
