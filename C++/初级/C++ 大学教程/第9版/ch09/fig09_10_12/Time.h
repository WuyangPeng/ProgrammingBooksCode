// Fig. 9.10: Time.h
// Time class declaration.
// Member functions defined in Time.cpp

// prevent multiple inclusions of header 
#ifndef TIME_H  
#define TIME_H 

class Time 
{
public:
   explicit Time( int = 0, int = 0, int = 0 );
   void setTime( int, int, int );
   unsigned int getHour() const;
   unsigned int &badSetHour( int ); // dangerous reference return
private:
   unsigned int hour;
   unsigned int minute;
   unsigned int second;
}; // end class Time

#endif

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
