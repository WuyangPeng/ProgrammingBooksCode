/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cUnreliableQueueIn.cpp: implementation of the cUnreliableQueueIn class.
//
//////////////////////////////////////////////////////////////////////

#include "cUnreliableQueueIn.h"
#include "cNetError.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cUnreliableQueueIn::cUnreliableQueueIn() : cMonitor()
{
  d_currentPacketID = 0;
}

cUnreliableQueueIn::~cUnreliableQueueIn()
{
  Clear();
}


void cUnreliableQueueIn::Clear()
{
  cMonitor::MutexOn();

  d_packets.clear();

  cMonitor::MutexOff();
}


// If we wanted to spend a lot of time checking, we could see if packet (packetID-n)
// Was still queued and, if so, insert the packet.  I'm feeling lazy tonight.
void cUnreliableQueueIn::AddPacket( DWORD packetID, char *pData, unsigned short len, DWORD receiveTime )
{
  if( pData == NULL ||
      len == 0 ||
      packetID < d_currentPacketID )
    return;

  // Create the packet.
  cDataPacket *pPacket;

  pPacket = new cDataPacket;
  if( pPacket == NULL )
    throw cNetError( L"cUnreliableQueueIn::AddPacket() - insufficient memory." );

  pPacket->Init( receiveTime, packetID, len, pData );
  if( packetID >= d_currentPacketID )
    d_currentPacketID = packetID + 1;

  // Add the packet to the queue.
  cMonitor::MutexOn();

  d_packets.push_back( pPacket );

  cMonitor::MutexOff();
}


cDataPacket *cUnreliableQueueIn::GetPacket()
{
  if( d_packets.empty() == true )
    return NULL;

  cDataPacket *pPacket;

  cMonitor::MutexOn();

  pPacket = *d_packets.begin();
  d_packets.pop_front();

  cMonitor::MutexOff();

  return pPacket;
}

