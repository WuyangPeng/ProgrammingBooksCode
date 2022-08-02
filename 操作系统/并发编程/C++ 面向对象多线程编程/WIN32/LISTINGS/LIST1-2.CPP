// Listing 1-2
// Some of the definitions for the rational class
// that demonstrate how rational class
// semantics are enforced

#include "rational.h"


       rational::rational(long Num,long Den)
       {
         Numerator = Num;
         if(Den == 0){
            Exception.message("Zero Is A Invalid Denominator");
            throw Exception;
         }
         Denominator = Den;
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
      
      void rational::assign(long X, long Y)
      {
      
        if(Y == 0){
           Exception.message("Zero Is A Invalid Denominator");
           throw Exception;
        }
        Numerator = X;
        Denominator = Y;
      }
      
