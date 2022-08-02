//###################################################################################
//#																					#
//#			Chapter 5 - Bind_SocketObject program									#		
//#																					#
//#						Demonstrates using the Bind SocketObject function			#
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
		ServerSocketObject.Disconnect();
	}
	else {
		cout << "**ERROR** Could Not Bind" << endl;
	}
	WSACleanup();
}



