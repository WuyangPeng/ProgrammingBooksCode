/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _GAMEERRORS_H
#define _GAMEERRORS_H

#include <string>
#include "GameGlobals.h"

//==========--------------------------  

/**
 * This code is slow, using dynamic memory, but since we only use them
 * when something Really Bad happens, the user won't notice that their
 * application exits abmornally a few nanoseconds slower than usual
 */
class cGameError
{
	std::wstring m_errorText;
public:
	cGameError( const TCHAR* errorText )
	{
		DP1(L"***\n*** [ERROR] cGameError thrown! text: [%s]\n***\n", errorText );
		m_errorText = std::wstring( errorText );
	}

	const TCHAR* GetText()
	{
		return m_errorText.c_str();
	}
};

//==========--------------------------  

enum eResult
{
	resAllGood		= 0, // function passed with flying colors
	resFalse		= 1, // function worked and returns value 'false'
	resFailed		= -1, // function failed miserably
	resNotImpl		= -2, // function has not been implemented
	resForceDWord = 0x7FFFFFFF
};

inline bool Succeeded( eResult in )
{
	if( in >= 0 )
		return true;
	return false;
}

inline bool Failed( eResult in )
{
	if( in < 0 )
		return true;
	return false;
}

#endif //_GAMEERRORS_H