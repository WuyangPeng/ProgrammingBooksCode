#include "select.h"
#include <iostream>

int main() {
	Select< sizeof(int)==sizeof(long), int, long >::Result temp = 0;
	
	const char CM = CHAR_MAX;
	
	const Select<__LINE__<=CM,char,long>::Result curLine1 = __LINE__;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	const Select<__LINE__<=CM,char,long>::Result // line #127!
    	curLine2 = __LINE__;

	std::cout << "curLine1 = " << long(curLine1) << '\t' << "curLine2 = " << long(curLine2) << std::endl;
	
	return 0;
}
