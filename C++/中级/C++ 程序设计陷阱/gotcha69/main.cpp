#include <iostream>
#include "firewall.h"

int main() {
	char *rawmsg1 = "\05rest of message";
	Firewall fw;
	RawMsgSource rms1( rawmsg1 );
	if( Msg *m = fw.genMsg( rms1 ) ) {
		m->op1();
		delete m;
	}
	else
		std::cout << "Unknown message type" << std::endl;
	
	char *rawmsg2 = "\11a different type of message";
	RawMsgSource rms2( rawmsg2 );
	if( Msg *m = fw.genMsg( rms2 ) ) {
		m->op1();
		delete m;
	}
	else
		std::cout << "Unknown message type" << std:: endl;

	return 0;
}
