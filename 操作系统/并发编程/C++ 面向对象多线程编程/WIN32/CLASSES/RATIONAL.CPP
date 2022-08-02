
#include "rational.h"
#include <math.h>
#include <stdlib.h>


rational::rational(long Num,long Den)
{
  Numerator = Num;
  if(Den == 0){
     Exception.message("Zero Is A Invalid Denominator");
     throw Exception;
  }
  Denominator = Den;
}

rational::rational(const rational &X)
{
     Numerator = X.Numerator;
     Denominator = X.Denominator;
}




//============================[*]=============================================
// This member function provides multiplication for two rational numbers
// It takes an explicit parameter and has an implicit operand.
// This function computes n/m = a/b * x/y. It computes the product as
// (n = a * x) and (m = b * y) the function returns n/m as the result.
// The function also reduces n/m to its lowest terms.
//==========================================================================



rational rational::operator*(const rational &X)
{
  rational Temp;
  Temp.Numerator = Numerator * X.Numerator;
  Temp.Denominator = Denominator * X.Denominator;
  Temp.reduce();
  return Temp;

}




//=======================[+]====================================================
// This member function allows the rational object to add to rational numbers in
// exact form i.e 2/4 + 1/4 = 3/4.
// The member function will return the result of the addition in reduced form.
//============================================================================



rational rational::operator+(const rational &X)
{
  rational Temp;
  Temp.Numerator = (Numerator * X.Denominator) + (Denominator * X.Numerator);
  Temp.Denominator = Denominator * X.Denominator;
  Temp.reduce();
  return Temp;
}




rational &rational::operator=(const rational &X)
{
  Numerator = X.Numerator;
  Denominator = X.Denominator;
  return *this;
}




void rational::assign(long X, long Y)
{

  if(Y == 0){
     Exception.message("Zero Is A Invalid Denominator");
     throw Exception;
  }
  Numerator = X;
  Denominator = Y;
}

int rational::operator()(const rational &X, const rational &Y) const
{
    long int ResultX;
    long int ResultY;
    ResultX = X.Numerator / X.Denominator;
    ResultY = Y.Numerator / Y.Denominator;
    if(ResultX < ResultY){
       return(1);
    }
    else{
          return(0);
    }
}
 
long rational::denominator(void) const
{
  return(Denominator);
}


long rational::numerator(void) const
{
  return(Numerator);
}


rational rational::operator/(const rational &X)
{
  if(X.Denominator == 0){
     Exception.message("Divison By Zero Undefined");
     throw Exception;
  }
  rational Temp;
  Temp.Numerator = Numerator * X.Denominator;
  Temp.Denominator = Denominator * X.Numerator;
  Temp.reduce();
  return Temp;
}


int rational::operator==(rational X)
{
  reduce();
  X.reduce();
  if((Numerator == X.Numerator) && (Denominator == X.Denominator)){
    return 1;
   }
   else
      return 0;
}




istream &operator>>(istream& in,rational &X)
{  
   char Junk;
   in >> X.Numerator;
   in >> Junk;
   in >> X.Denominator;
   return(in);
}

ostream &operator<<(ostream& out,rational X)
{
  if(X.Denominator < 0){
     X.Denominator *= -1;
    X.Numerator *= -1;
  }
  if(X.Numerator == X.Denominator){
     out << 1;

   }
    else
      if(X.Denominator == 1){
	out << X.Numerator;
      }
   else
   if (X.Numerator != X.Denominator){
      out << X.Numerator << "/" << X.Denominator;

   }
   return(out);


}



void rational::reduce(void)
{
  long Largest;
  long Number;
  long Remainder;
  if(labs(Numerator) >= labs(Denominator)){
     Largest = Numerator;
     Number = Denominator;
   }
   else{
      Largest = Denominator;
      Number = Numerator;
   }
  while(Number != 0){
    Remainder = Largest % Number;
    Largest = Number;
    Number = Remainder;
   }
   if(Largest == 0){
      Exception.message("Division By Zero is Undefined");
      throw Exception;
   }
   Numerator = Numerator / Largest;
   Denominator = Denominator / Largest;

}



rational rational::operator-(const rational &X)
{
  rational Temp;
  Temp.Numerator = (Numerator * X.Denominator) - (Denominator * X.Numerator);
  Temp.Denominator = Denominator * X.Denominator;
  Temp.reduce();
  return Temp;
}
//=================================================================================









