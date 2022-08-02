/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _LOGINNM_H
#define _LOGINNM_H

#include "NetMessages.h"

//=================================================================

/**
 * Message: Login Request
 * ID: 1
 */
class cNM_LoginRequest 
: public cNetMessage
{
	char m_name[32];
public:

	cNM_LoginRequest( string clientName );
	cNM_LoginRequest(){}

	virtual int SerializeTo( unsigned char* pOutput);
	virtual void SerializeFrom( unsigned char *pFromData, int datasize );
	virtual void Exec();

protected:
};

//=================================================================

/**
 * Message: Login Acceptance
 * ID: 2
 */
class cNM_LoginAccepted 
: public cNetMessage
{
	int m_playerID; // the newly minted player ID.
public:

	cNM_LoginAccepted( int playerID );
	cNM_LoginAccepted(){}

	virtual int SerializeTo( unsigned char* pOutput );
	virtual void SerializeFrom( unsigned char *pFromData, int datasize );
	virtual void Exec();

protected:
};

/**
 * Message: Logout Notification
 * ID: 7
 */
class cNM_LogoutNotice 
: public cNetMessage
{
	int m_playerID; // ID of the player leaving
public:

	cNM_LogoutNotice( int playerID );
	cNM_LogoutNotice(){}

	virtual int SerializeTo( unsigned char* pOutput );
	virtual void SerializeFrom( unsigned char *pFromData, int datasize );
	virtual void Exec();

protected:
};


/**
 * Message: New Player notification
 * ID: 8
 */
class cNM_NewPlayer 
: public cNetMessage
{
	int m_entID;
	int m_score;
	char m_name[32];
	sEntState m_state;
public:

	cNM_NewPlayer( int id, int score, string clientName, sEntState state );
	cNM_NewPlayer(){}

	virtual int SerializeTo( unsigned char* pOutput );
	virtual void SerializeFrom( unsigned char *pFromData, int datasize );
	virtual void Exec();

protected:
};


#endif //_LOGINNM_H