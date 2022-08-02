//###################################################################################
//#																					#
//#			Chapter 5 - Bind, Listen Functionality									#		
//#																					#
//#						Demonstrates all functions required to call listen()		#
//#																					#
//#						Todd Barron, 10/15/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include <winsock.h>
#include <stdio.h>

//
// ----> Main Program Function (REQUIRED)
//
void main(void)
{
	SOCKET		skSocket;
	sockaddr_in saServerAddress;
	int			iPort = 6000;
	int			iStatus;
	WSADATA		wsaData;
	WORD		wVersionRequested;

	// Tell WinSock we want version 2
	wVersionRequested = MAKEWORD( 2, 0 );

	// Initialize the socket handle
	skSocket = INVALID_SOCKET;

	// Startup WinSock
	iStatus = WSAStartup( wVersionRequested, &wsaData );

	// Create the socket
	skSocket = socket( AF_INET, SOCK_STREAM, 0 );
	
	// Check if there was an error
	if( skSocket == INVALID_SOCKET ) {
		cout << "**ERROR** Could Not Create Socket" << endl;
		// Clean up WinSock
		WSACleanup();
		exit(1);
	}

	cout << "<-- SOCKET CREATED -->" << endl;

	// Clear out the socket address structure
	memset(&saServerAddress, 0, sizeof(sockaddr_in));

	// Initialize the socket address structure
	saServerAddress.sin_family = AF_INET;
	saServerAddress.sin_addr.s_addr = htonl( INADDR_ANY );
	saServerAddress.sin_port = htons( iPort );

	// Attempt to bind
	if( bind( skSocket, (sockaddr*) &saServerAddress, sizeof(sockaddr) ) == SOCKET_ERROR ) {
		cout << "**ERROR** Could Not Bind" << endl;
		// Clean up WinSock
		WSACleanup();
		exit(1);
	}

	cout << "<-- SOCKET BOUND -->" << endl;

	// Listen for a connection
	iStatus = listen( skSocket, 32 );

	if( iStatus == SOCKET_ERROR ) {
		cout << "**ERROR** Error Listening" << endl;
		// Close the socket
		closesocket(skSocket);
		// Clean up WinSock
		WSACleanup();
		exit(1);
	}

	cout << "<-- SOCKET LISTENING -->" << endl;
	
	// Close the socket
	closesocket(skSocket);

	// Clean up WinSock
	WSACleanup();
}
