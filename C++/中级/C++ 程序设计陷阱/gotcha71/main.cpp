#include "msg.h"
#include "msgdecorator.h"

int main() {

	XMsg *xmsg = new XMsg;
	xmsg->send(); // call XMsg::send
	xmsg->Msg::send(); // call hidden/overridden Msg::send
	
	Msg *msg = xmsg;
	msg = new BeepDecorator( msg );
	msg->send();

	return 0;
}
