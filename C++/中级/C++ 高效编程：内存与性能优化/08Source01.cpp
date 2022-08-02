#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include "BookTools.h"

#define OS2                     1
#define WINDOWS95       2
#define LINUX           3

#define NETSCAPE 1
#define EXPLORER 2


class ComputerUser
{
public:

  // constructor
  ComputerUser()            
  { 
    favouriteOS = 0; 
  } 

  ComputerUser(char *n, int OS)
  {   
    strcpy(name, n);
    favouriteOS = OS; 
  } 

  // destructor
  ~ComputerUser()
  {

  }
  
  // interface
  void SetOS(int OS)    
  { 
    favouriteOS = OS; 
  }  

  void SetName(const char *s)
  { 
    strcpy(name, s); 
  }
  
private:

  // data
  int favouriteOS;
  char name[50];
};


class Internetter: public ComputerUser
{
public:

  // constructor
  Internetter()
  { 
     favouriteBrowser = 0; 
  }
  
  Internetter(char *n, int OS, int browser)    
  { 
    SetName(n);
    SetOS(OS);
    favouriteBrowser = browser; 
  }

  // destructor
  ~Internetter()     
  {

  }
  
  // interface
  void SetBrowser(int browser)  
  { 
    favouriteBrowser = browser; 
  }  
  
private:

  // data
  int favouriteBrowser;
};


class Internetter2: public ComputerUser
{
public:
  
  // constructor
  Internetter2()            { favouriteBrowser = 0; }
  Internetter2(char *n, int OS, int browser) 
  : ComputerUser(n, OS)   
  { 
    favouriteBrowser = browser; 
  }
  
  // destructor
  ~Internetter2()     {}
  
  // interface
  void SetBrowser(int browser)  
  { 
          favouriteBrowser = browser; 
  }  
  
private:
  // data
  int favouriteBrowser;
};


class ExtendedComputerUser
{
public:

  // constructor
  ExtendedComputerUser()            
  { 
    favouriteOS = 0; 
  } 

  ExtendedComputerUser(char *n, int OS, int browser)
  {   
    strcpy(name, n);
    favouriteOS = OS; 
    favouriteBrowser = browser; 
  } 
  // destructor
  ~ExtendedComputerUser()   {}
  
  // interface
  void SetOS(int OS)    { favouriteOS = OS; }  
  void SetBrowser(int browser)  { favouriteBrowser = browser; }  
  void SetName(const char *s)  { strcpy(name, s); }
  
private:
  // data
  int favouriteOS;
  int favouriteBrowser;
  char name[40];
};


long my_fn1()
{
  Internetter *p;
  
  for (long i = 0; i < 2000000; i++)
  {
    p = new Internetter;
    p->SetName("John");  
    p->SetOS(LINUX);
    p->SetBrowser(NETSCAPE);
    delete p;
  }
  return 0;
}


long my_fn2()
{
  Internetter *p;
  
  for (long i = 0; i < 2000000; i++)
  {
    p = new Internetter("John", LINUX, NETSCAPE);
    delete p;
  }
  return 0;
}


long my_fn3()
{
  Internetter2 *p;
  
  for (long i = 0; i < 2000000; i++)
  {
    p = new Internetter2 ("John", LINUX, NETSCAPE);
    delete p;
  }
  return 0;
}


long my_fn4()
{
  ExtendedComputerUser *p;
  
  for (long i = 0; i < 2000000; i++)
  {
    p = new ExtendedComputerUser("John", LINUX, NETSCAPE);
    delete p;
  }
  return 0;
}

void main(int argc, char *argv)
{
  for(;;)
  {  
    cout << "1:" << time_fn(my_fn1) << endl;
    cout << "2:" << time_fn(my_fn2) << endl;
    cout << "3:" << time_fn(my_fn3) << endl;
    cout << "4:" << time_fn(my_fn4) << endl;
  }
}