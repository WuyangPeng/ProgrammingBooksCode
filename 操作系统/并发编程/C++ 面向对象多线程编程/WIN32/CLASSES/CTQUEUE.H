#include <deque.h>
#include "ctmutex.h"

template <class T> class lqueue : virtual private named_mutex,
				  virtual private event_mutex{
protected:
    deque<T> SafeQueue;
public:
    lqueue(char *MName,int Own,char *EName,int Initial,
	  unsigned long Dur);
    inline void insert(T X);
    inline T remove(void);
    inline T front(void);
    inline T back(void);
    inline unsigned int empty(void);
    inline unsigned int size(void);
    inline void erase(void);
    inline void reversed(void);
    void wait(void);
	 void broadCast(void);

};
