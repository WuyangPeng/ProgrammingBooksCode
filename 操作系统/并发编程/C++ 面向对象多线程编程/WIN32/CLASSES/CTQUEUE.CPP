#include <cstring.h>
#include <windows.h>
#include "ctqueue.h"
#include "ctevent.h"



template <class T> lqueue<T>::lqueue(char *MName,int Own,char *EName,
			       int Initial,unsigned long Dur) :
			       named_mutex(MName,Own),
			       event_mutex(EName,Initial,Dur)
{
}

template <class T> void lqueue<T>::insert(T X)
{
     lock();
     SafeQueue.push_back(X);
     unlock();
}


template <class T> T lqueue<T>::remove(void)
{

    T Temp;
    lock();
    Temp = SafeQueue.front();
    SafeQueue.pop_front();
    unlock();
    return(Temp);
}

template <class T> void lqueue<T>::reversed(void)
{
     lock();
     reverse(SafeQueue.begin(),SafeQueue.end());
     unlock();
}

template <class T> T lqueue<T>::front(void)
{
    return(SafeQueue.front());
}


template <class T> T lqueue<T>::back(void)
{

      return(SafeQueue.back());
}


template <class T> unsigned int lqueue<T>::size(void)
{
      return(SafeQueue.size());
}

template <class T> unsigned int lqueue<T>::empty(void)
{
      return(SafeQueue.empty());
}

template <class T> void lqueue<T>::erase(void)
{
    lock();
    SafeQueue.erase(SafeQueue.begin(),SafeQueue.end());
    unlock();
}


template <class T> void lqueue<T>::wait(void)
{
      waitEvent();
}

template <class T> void lqueue<T>::broadCast(void)
{
      postEvent();
}