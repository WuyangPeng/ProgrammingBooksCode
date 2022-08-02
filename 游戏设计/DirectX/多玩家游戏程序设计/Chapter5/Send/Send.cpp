//###################################################################################
//#																					#
//#			Chapter 5 - Connect Functionality										#		
//#																					#
//#						Demonstrates the send() function							#
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
	int			iPort = 80,iStatus;
	WSADATA		wsaData;
	WORD		wVersionRequested;
	LPHOSTENT	lpHost;
	char		szHost[128];
	char		szSendBuffer[256];
	int			iBytesSent;

	// Init the host value, change this IP to whatever valid IP you wish
	sprintf(szHost,"www.lostlogic.com");

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

	// Initialize the server address data structure
	memset(&saServerAddress,0,sizeof(sockaddr_in));
	// Set this by default
	saServerAddress.sin_family = AF_INET;
	// Load the IP Address
	saServerAddress.sin_addr.s_addr = inet_addr(szHost);

	// If the host specified is not an IP Address we must look up the value
	if( saServerAddress.sin_addr.s_addr == INADDR_NONE )
	{
		cout << "<-- LOOKING UP HOST IP -->" << endl;
		// Get the host name
		lpHost = gethostbyname(szHost);
		// Check if we got something back
		if (lpHost != NULL) {
			// Load the server address with the host information
			saServerAddress.sin_addr.s_addr = ((LPIN_ADDR)lpHost->h_addr)->s_addr;
		}
		else {
			cout << "**ERROR** Could Not Locate Host" << endl;
			// Clean up WinSock
			WSACleanup();
			exit(1);
		}
	}

	// Set the Server Port
	saServerAddress.sin_port = htons(iPort);

	// Attempt to connect to the server
	iStatus = connect(skSocket, (struct sockaddr*)&saServerAddress,sizeof(sockaddr));
	
	// Check if there was an error
	if( iStatus == SOCKET_ERROR ) {
		cout << "**ERROR** Could Not Connect To Server" << endl;
		// Clean up WinSock
		WSACleanup();
		exit(1);
	}

	cout << "<-- CONNECTED TO SERVER -->" << endl;

	sprintf(szSendBuffer,"Test Data");
	iBytesSent = send(skSocket,szSendBuffer,256,0);

	cout << "<-- SENT " << iBytesSent << " BYTES -->" << endl;

	// Close the socket
	closesocket(skSocket);

	// Clean up WinSock
	WSACleanup();
}
 
 
