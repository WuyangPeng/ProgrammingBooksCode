/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cNetError.cpp: implementation of the cNetError class.
//
//////////////////////////////////////////////////////////////////////
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>  

#include "cNetError.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cNetError::cNetError()
{
  d_text[ 0 ] = NULL;
}


cNetError::~cNetError()
{
}


cNetError::cNetError( const TCHAR *pText )
{
  if( pText == NULL )
    wcscpy_s( d_text, sizeof(d_text), L"Unspecified." );
  else
    wcscpy_s( d_text, sizeof(d_text), pText );

  OutputDebugString( L"Network Error: " );
  OutputDebugString( d_text );
  OutputDebugString( L"\n" );
}

