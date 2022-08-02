/*********************************************************************

  Filename:  clock.cpp
  Section:   11.4   The this Pointer
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Clock to show overloading
//  Title: clock

#include <iostream.h>

class clock {
public:
   clock(unsigned long int i); //constructor conversion
   void  print();              //formatted printout
   void  tick();               //add one second
   clock  operator++() { tick(); return(*this); }
private:
   unsigned long int  tot_secs, secs, mins, hours, days;
};


inline clock::clock(unsigned long int i)
{
   tot_secs = i;
   secs = tot_secs % 60;
   mins = (tot_secs / 60) % 60;
   hours = (tot_secs / 3600) % 24;
   days = tot_secs / 86400;
}

void clock::tick()
{
   clock  temp = clock(++tot_secs);

   secs = temp.secs;
   mins = temp.mins;
   hours = temp.hours;
   days = temp.days;
}

void clock::print()
{
   cout << days << " d :" << hours << " h :"
	<< mins << " m :" << secs << " s\n";
}

int main()
{
   clock t1(59), t2(172799);  //min - 1 sec and 2 days - 1 sec


   cout << "initial times are\n";
   t1.print();
   t2.print();
   ++t1;  ++t2;          //t1++; t2++ are also possible
   cout << "after one second times are\n";
   t1.print();
   t2.print();
}
