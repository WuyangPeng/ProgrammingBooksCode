/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// Macros.h - macros, defines, typedefs, etc.
//
//////////////////////////////////////////////////////////////////////

#if !defined( __MACROS_H )
#define __MACROS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined( _CONSOLE )

#define OUTPUTREPORT0( a )            { wprintf_s( a ); }
#define OUTPUTREPORT1( a, b )         { wprintf_s( a, b ); }
#define OUTPUTREPORT2( a, b, c )      { wprintf_s( a, b, c ); }
#define OUTPUTREPORT3( a, b, c, d )   { wprintf_s( a, b, c, d ); }

#else // !defined( _CONSOLE )

#define OUTPUTREPORT0( a ) \
{ \
  OutputDebugString( a ); \
}


#define OUTPUTREPORT1( a, b ) \
{ \
  TCHAR outputBuffer[ 1000 ]; \
  swprintf_s( outputBuffer, 1000, a, b ); \
  OutputDebugString( outputBuffer ); \
}


#define OUTPUTREPORT2( a, b, c ) \
{ \
  TCHAR outputBuffer[ 1000 ]; \
  swprintf_s( outputBuffer, 1000, a, b, c ); \
  OutputDebugString( outputBuffer ); \
}


#define OUTPUTREPORT3( a, b, c, d ) \
{ \
  TCHAR outputBuffer[ 1000 ]; \
  swprintf_s( outputBuffer, 1000, a, b, c, d ); \
  OutputDebugString( outputBuffer ); \
}

#endif  // defined( _CONSOLE )

#if defined( _DEBUG )

// printf() a lot of information
#define _DEBUG_VERBOSE

// Drop 1 in _DEBUG_DROPTEST random packets to see how the system handles it.
// Undefine _DEBUG_DROPTEST to turn it off.  _DEBUG_DROPTEST > 1.
//#define _DEBUG_DROPTEST   4

// Queue an outgoing message for at least _DEBUG_PINGTEST ms
// Undefine _DEBUG_PINGTEST to turn it off.  _DEBUG_PINGTEST > 0.
//#define _DEBUG_PINGTEST   100

// printf() some ping information
//#define _DEBUG_TIMING

// Clock synch testing information
//#define _DEBUG_CLOCK

#endif  // !defined( _DEBUG )


// Convert bits to bytes.
#define BYTESREQUIRED( x )  ( ( x >> 3 ) + ( x & 0x7 != 0 ) )


#endif