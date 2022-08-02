/*********************************************************************

  Filename:  my_types.h
  Section:   5      Linkage
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// this works with fncs.cpp and mainfile.cpp

//my_types.h header file

#ifndef MYTYPE      //avoid multiple inclusion problem
#define MYTYPE

typedef char* c_string;    //c_string pointer to char
typedef void (*ptr_f)();   //pointer to function

void  foo(c_string s);     //function prototypes
void  title();
void  pr_onoff();

enum { OFF, ON };          //global enumerator
extern int  x;             //x defined in mainfile.c
#endif

