//###################################################################################
//#																					#
//#			Chapter 5 - Send_SocketObject program									#		
//#																					#
//#						Demonstrates using the Send SocketObject function			#
//#																					#
//#						Todd Barron, 10/12/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include "..\\socketobject\\SocketObject.h"

//
// ----> Main Program Function (REQUIRED)
//
void main( void )
{
	SocketObject	ClientSocketObject;	
	int				iPort = 80;		// HTTP Port
	char			szSendBuffer[256];
	int				iBytesSent;
	
	cout << "<-- ATTEMPTING CONNECTION -->" << endl;

	// Attempt to connect
	if ( ClientSocketObject.Connect( "www.lostlogic.com", iPort ) ) {
		cout << "<-- SOCKET CONNECTED -->" << endl;

		sprintf(szSendBuffer,"TEST DATA");
		iBytesSent = ClientSocketObject.Send(szSendBuffer,256,0);
		cout << "<-- SENT " << iBytesSent << " BYTES -->" << endl;
	}		
	else {
		cout << "**ERROR** Could Not Connect" << endl;
	}
	WSACleanup();
}
