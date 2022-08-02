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
	char			szRecvBuffer[32768];
	int				iBytesReceived;
	
	cout << "<-- ATTEMPTING CONNECTION -->" << endl;

	// Attempt to connect
	if ( ClientSocketObject.Connect( "www.lostlogic.com", iPort ) ) {
		cout << "<-- SOCKET CONNECTED -->" << endl;

		// Load the request buffer
		sprintf(szSendBuffer,"GET / HTTP/1.0\n\n");
		// Send the request
		iBytesSent = ClientSocketObject.Send(szSendBuffer,256,0);
		cout << "<-- SENT " << iBytesSent << " BYTES -->" << endl;
		
		// Receive the response
		iBytesReceived = ClientSocketObject.Recv(szRecvBuffer,32768,0);
		cout << "<-- RECEIVED " << iBytesReceived << " BYTES -->" << endl;
		// Output what was received
		cout << szRecvBuffer << endl;
	}		
	else {
		cout << "**ERROR** Could Not Connect" << endl;
	}
	WSACleanup();
}
