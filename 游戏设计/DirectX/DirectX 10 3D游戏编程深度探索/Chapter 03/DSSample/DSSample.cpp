/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include <vector>
#include <string>
using namespace std;

class cDSSampleApp : public cApplication, public iKeyboardReceiver
{
	vector< cSound* > m_sounds[6];
	wstring m_names[6];

	int m_states[6]; // states of the keys 1-6

public:

	void PlaySound( int num );

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();

	cDSSampleApp() :
		cApplication()
	{
		m_title = wstring( L"DirectSound Sample" );
		m_width = 640;
		m_height = 480;

		for( int i=0; i<6; i++ ) m_states[i] = 0;
	}

	~cDSSampleApp()
	{
		for( int i=0; i<6; i++ )
		{
			for( int i2=0; i2< m_sounds[i].size(); i2++ )
			{
				delete m_sounds[i][i2];
			}
		}
	}

	virtual void KeyUp( int key );
	virtual void KeyDown( int key );

};


cApplication* CreateApplication()
{
	return new cDSSampleApp();
}


void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}


void cDSSampleApp::SceneInit()
{
	m_names[0] = wstring(L"..\\media\\keg.wav");
	m_names[1] = wstring(L"..\\media\\crash1.wav");
	m_names[2] = wstring(L"..\\media\\crash2.wav");
	m_names[3] = wstring(L"..\\media\\bass.wav");
	m_names[4] = wstring(L"..\\media\\snare.wav");
	m_names[5] = wstring(L"..\\media\\hihat.wav");

	Input()->GetKeyboard()->SetReceiver( this );

	for( int i=0; i<6; i++ )
	{
		m_sounds[i].push_back( new cSound( (TCHAR*)m_names[i].c_str() ) );
	}
}


void cDSSampleApp::PlaySound( int num )
{
	/**
	 * iterate through the vector, looking
	 * for a sound that isn't currently playing.
	 */
	vector<cSound*>::iterator iter;
	for( iter = m_sounds[num].begin(); iter != m_sounds[num].end(); iter++ )
	{
		if( !(*iter)->IsPlaying() )
		{
			(*iter)->Play();
			return;
		}
	}

	/**
	 * A sound wasn't found.  Create a new one.
	 */
	DP(L"spawning a new sound\n");

	cSound* pNew = new cSound( *m_sounds[num][0] );
	m_sounds[num].push_back( pNew );
	m_sounds[num][ m_sounds[num].size() - 1 ]->Play();
}


void cDSSampleApp::DoFrame( float timeDelta )
{
	// Clear the previous contents of the backbuffer
	float colClear[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	Graphics()->Clear(colClear);

	// Set up the strings
	wstring help;
	help += L"DirectSound Sample application\n";
	help += L"Vocal Percussion with Adrian Perez\n";
	help += L"  [1]: Keg drum\n";
	help += L"  [2]: Crash 1\n";
	help += L"  [3]: Crash 2\n";
	help += L"  [4]: Bass drum\n";
	help += L"  [5]: Snare drum\n";
	help += L"  [6]: Hi-Hat\n";

	// Tell Direct3D we are about to start rendering
	//Graphics()->GetDevice()->BeginScene();

	// Output the text
	Graphics()->DrawTextString( 1, 1, D3DXCOLOR(1, 1, 1, 1), help.c_str() );

	// Tell Direct3D we are done rendering
	//Graphics()->GetDevice()->EndScene();

	// Present the back buffer to the primary surface
	Graphics()->Present();
}


void cDSSampleApp::KeyDown( int key )
{
	switch( key )
	{
	case DIK_1:
		if( !m_states[0] )
		{
			m_states[0] = 1;
			PlaySound(0);
		}
		break;
	case DIK_2:
		if( !m_states[1] )
		{
			m_states[1] = 1;
			PlaySound(1);
		}
		break;
	case DIK_3:
		if( !m_states[2] )
		{
			m_states[2] = 1;
			PlaySound(2);
		}
		break;
	case DIK_4:
		if( !m_states[3] )
		{
			m_states[3] = 1;
			PlaySound(3);
		}
		break;
	case DIK_5:
		if( !m_states[4] )
		{
			m_states[4] = 1;
			PlaySound(4);
		}
		break;
	case DIK_6:
		if( !m_states[5] )
		{
			m_states[5] = 1;
			PlaySound(5);
		}
		break;
	}
}

void cDSSampleApp::KeyUp( int key )
{
	switch( key )
	{
	case DIK_1:
		m_states[0] = 0;
		break;
	case DIK_2:
		m_states[1] = 0;
		break;
	case DIK_3:
		m_states[2] = 0;
		break;
	case DIK_4:
		m_states[3] = 0;
		break;
	case DIK_5:
		m_states[4] = 0;
		break;
	case DIK_6:
		m_states[5] = 0;
		break;
	}
}