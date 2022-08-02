#include "ctevent.h"

multiple_event_mutex::multiple_event_mutex(char *MName, int ENum,long int WaitType,int Initial)
{
    int N;
    EventNumber = ENum;
    ConditionList = new SEMRECORD[ENum];
    for(N = 0;N < ENum;N++)
    {
	if(DosCreateEventSem(NULL,&EventMutex,0,Initial)){
	   EventException.message("Could Not Create Event Semaphore");
	   throw EventException;
	}
	ConditionList[N].hsemCur = &EventMutex;
	ConditionList[N].ulUser = N;
    }
    if(DosCreateMuxWaitSem(MName,&MultipleEventMutex,sizeof(ConditionList),
			   ConditionList,WaitType)){
       EventException.message("Could Not Create Multiple Event Semaphore");
       throw EventException;

    }
}

multiple_event_mutex::multiple_event_mutex(char *MName)
{
     if(DosOpenMuxWaitSem(MName,&MultipleEventMutex)){
	 EventException.message("Could Not Open Event Semaphore");
	   throw EventException;
     }}

multiple_event_mutex::~multiple_event_mutex(void)
{

     if(DosCloseMuxWaitSem(MultipleEventMutex)){
	 EventException.message("Could Not Close Event Semaphore");
	   throw EventException;
     }
     delete ConditionList;
}

int multiple_event_mutex::duration(void)
{
    return(Duration);
}

void multiple_event_mutex::duration(int X)
{

    Duration = X;
}

void multiple_event_mutex::postEvent(int X)
{
   EventMutex = (HEV) ConditionList[X].hsemCur;
   DosPostEventSem(EventMutex);
}

void multiple_event_mutex::waitEvents(void)
{

    unsigned long User;
    DosWaitMuxWaitSem(MultipleEventMutex,SEM_INDEFINITE_WAIT,&User);
}
