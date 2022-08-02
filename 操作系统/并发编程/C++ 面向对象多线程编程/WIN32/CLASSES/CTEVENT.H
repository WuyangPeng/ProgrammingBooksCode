#include "eclasses.h"
#include <windows.h>



class event_mutex{
protected:
	 HANDLE EventMutex;
    char MutexName[81];
    int InitallySet;
    general_exception EventException;
	 DWORD EventWait;
public:
	 event_mutex(char *MName, BOOL Initial = 0, unsigned long Dur = INFINITE);
	 void postEvent(void);
	 void waitEvent(void);
	 ~event_mutex(void);
};






