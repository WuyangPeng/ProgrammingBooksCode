//###################################################################################
//#																					#
//#			Chapter 5 - Listen_SocketObject program									#		
//#																					#
//#						Demonstrates using the Listen SocketObject function			#
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
	int				iPort = 6000;
	
	// Attempt to bind
	if ( ServerSocketObject.Bind( iPort ) ) {
		cout << "<-- SOCKET BOUND -->" << endl;
		
		if( ServerSocketObject.Listen() != SOCKET_ERROR ) {
			cout << "<-- SOCKET LISTENING -->" << endl;
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
