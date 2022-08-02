#include "ctevent.h"
#include <windows.h>



event_mutex::event_mutex(char *MName, BOOL Initial, unsigned long Dur)
{

	  strcpy(MutexName,MName);
	  EventMutex = CreateEvent(NULL,FALSE, Initial,MutexName);
	  if(!EventMutex){
			 EventException.message("Could Not Create Event Semaphore");
			 throw EventException;
	  }
	  EventWait = Dur;
}

void event_mutex::postEvent(void)
{
	 SetEvent(EventMutex);
}

void event_mutex::waitEvent(void)
{

	WaitForSingleObject(EventMutex,EventWait);

}

event_mutex::~event_mutex(void)
{

		if(!CloseHandle(EventMutex)){
		  EventException.message("Could Not Close Mutex");
		  throw EventException;
		}
}
