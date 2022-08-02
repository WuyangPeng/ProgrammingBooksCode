//###################################################################################
//#																					#
//#			Chapter 5 - Accept_SocketObject program									#		
//#																					#
//#						Demonstrates using the Accept SocketObject function			#
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
	SocketObject	ServerSocketObject;	
	SocketObject	ClientSocketObject;	
	int				iPort = 6000;
	
	// Attempt to bind
	if ( ServerSocketObject.Bind( iPort ) ) {
		cout << "<-- SOCKET BOUND -->" << endl;
		
		if( ServerSocketObject.Listen() != SOCKET_ERROR ) {
			cout << "<-- SOCKET LISTENING -->" << endl;
			if( ServerSocketObject.Accept( ClientSocketObject ) ) {
				cout << "<-- CLIENT ACCEPTED -->" << endl;
			}
			else {
				cout << "**ERROR** Could Not Accept" << endl;
			}
		}
		else {
			cout << "**ERROR** Could Not Listen" << endl;
		}
		ServerSocketObject.Disconnect();
	}
	else {
		cout << "**ERROR** Could Not Bind" << endl;
	}
	WSACleanup();
}
