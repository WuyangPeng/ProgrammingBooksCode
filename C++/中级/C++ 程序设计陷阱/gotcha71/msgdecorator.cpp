#include "msgdecorator.h"
#include <iostream>

void BeepDecorator::send() {
    MsgDecorator::send(); // do base class functionality
    std::cout << '\a' << std::flush; // additional behavior . . . 
}
