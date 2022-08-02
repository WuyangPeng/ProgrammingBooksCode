#include "eclasses.h"
#include <windows.h>
#include <cstring.h>


class mutex{
protected:
	 DWORD Duration;
	 HANDLE Mutex;
	 general_exception SemException;
public:
	 mutex(void);
	 ~mutex(void);
	 virtual void lock(void);
	 virtual void unlock(void);
};


class named_mutex : public mutex{
protected:
	 char MutexName[81];
	 BOOL InitiallyOwned;
public:
	named_mutex(void);
	named_mutex(char *MName, BOOL Owned = 0);
	named_mutex(string MName);
	DWORD lockDuration(void);
	void lockDuration(DWORD Dur);
};





