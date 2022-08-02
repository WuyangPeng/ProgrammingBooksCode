#include "mtration.h"


mt_rational::mt_rational(long Num,long Den)
{

  if(Den == 0){
     Exception.message("Zero Is A Invalid Denominator");
     throw Exception;
  }
  Numerator = Num;
  Denominator = Den;
}

mt_rational::mt_rational(const mt_rational &X)
{

     Numerator = X.Numerator;
     Denominator = X.Denominator;
}


mt_rational &mt_rational::operator=(const mt_rational &X)
{
   try{
	Mutex.lock();
	Numerator = X.Numerator;
	Denominator = X.Denominator;
	Mutex.unlock();
   }
   catch(general_exception &M)
   {
      Mutex.unlock();
      throw M;
   }
   return *this;
}

void mt_rational::assign(long X, long Y)
{

  if(Y == 0){
     Exception.message("Zero Is A Invalid Denominator");
     throw Exception;
  }
  try{
      Mutex.lock();
      Numerator = X;
      Denominator = Y;
      Mutex.unlock();
  }
  catch(general_exception &M)
  {
     Mutex.unlock();  
     throw M;
  }

}


