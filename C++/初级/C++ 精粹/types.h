/*********************************************************************

  Filename:  types.h
  Section:   4      Linkage Rules
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// This file works with linkage.cpp and fcns.cpp
// to illustrate linkage rules


typedef char *c_string;   //c_string is pointer to char
typedef void (*ptr_f)();  //pointer to function

void  foo(c_string s);     //function prototypes
void  title();
void  pr_onoff();

enum { OFF, ON };          //global enumerator
extern int  x;             //x defined in mainfile.c


