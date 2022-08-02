#include "msg.h"
#include <iostream>

void Msg::send()
	{ std::cout << "Sending Msg" << std::endl; }

void XMsg::send()
	{ std::cout << "Sending XMsg" << std::endl; }
