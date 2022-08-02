#include "../Fly3D.h"

void sound::reset()
{
	for( int i=0;i<MAX_SOUND_CHANNELS;i++ )
	{
		if (buf3d[i]) 
		{ 
			buf3d[i]->Release(); 
			buf3d[i]=0; 
		}
		if (buf[i]) 
		{ 
			buf[i]->Release(); 
			buf[i]=0; 
		}
		bufuse[i]=0;
	}
	total_time=0; 
}

int sound::load_wav(char *filename)
{
	if (directx==0)	return 0;

	fly_pak f;

	if (!f.open(filename)) return 0;

	reset();

	total_time=directx->load_wav_file(f.len,f.buf,&buf[0],&buf3d[0]);

	if (buf[0])
	for( int i=1;i<MAX_SOUND_CHANNELS;i++ )
	{
	buf[i]=directx->clone_sound(buf[0]);
	buf[i]->QueryInterface(IID_IDirectSound3DBuffer,(void **)(&buf3d[i]));
	}

	return total_time;
}

int sound::get_sound_instace()
{
	for( int i=0;i<MAX_SOUND_CHANNELS;i++ )
		if (bufuse[i]==0 && buf[i])
		{
			bufuse[i]=1;
			return i;
		}
	return -1;
}

void sound::free_sound_instance(int i)
{
	if (i>=0 && i<MAX_SOUND_CHANNELS)
	{
		bufuse[i]=0;
		buf[i]->Stop();
		buf[i]->SetCurrentPosition(0);
	}
}

sound::sound()
{
	for( int i=0;i<MAX_SOUND_CHANNELS;i++ )
	{
		buf[i]=0; 
		buf3d[i]=0;
		bufuse[i]=0;
	}
	total_time=0; 
};

sound::~sound()
{ 
	reset();
};
