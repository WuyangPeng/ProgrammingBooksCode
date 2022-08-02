//###################################################################################
//#																					#
//#			Chapter 5 - Connect_SocketObject program								#		
//#																					#
//#						Demonstrates using the Connect SocketObject function		#
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
	
	cout << "<-- ATTEMPTING CONNECTION -->" << endl;

	// Attempt to connect
	if ( ClientSocketObject.Connect( "www.lostlogic.com", iPort ) ) {
		cout << "<-- SOCKET CONNECTED -->" << endl;
	}		
	else {
		cout << "**ERROR** Could Not Connect" << endl;
	}
	WSACleanup();
}
