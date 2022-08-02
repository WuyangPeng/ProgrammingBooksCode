#include "term.h"
#include <cstdlib>

extern const char *terminalType = 0;
long InitMgr::count_ = 0;
void InitMgr::init() {
    if( !(terminalType = std::getenv( "TERM" )) )
    	terminalType = "VT100";
    // other initializations...
}

void InitMgr::cleanup() {
    // any required cleanup...
}
