/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cDataPacket.h: interface for the cDataPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDATAPACKET_H__4A115C41_D1D4_11D3_AE4F_00E029031C67__INCLUDED_)
#define AFX_CDATAPACKET_H__4A115C41_D1D4_11D3_AE4F_00E029031C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>


#define MAX_UDPBUFFERSIZE   4096


class cDataPacket  
{
public:
  char            d_data[ MAX_UDPBUFFERSIZE ];
  unsigned short  d_length,
                  d_timesSent;
  DWORD           d_id,
                  d_firstTime,
                  d_lastTime;

	cDataPacket();
	virtual ~cDataPacket();

  void Init( DWORD time, DWORD id, unsigned short len, char *pData );

  cDataPacket &operator=( const cDataPacket &otherPacket );
};


#endif // !defined(AFX_CDATAPACKET_H__4A115C41_D1D4_11D3_AE4F_00E029031C67__INCLUDED_)
