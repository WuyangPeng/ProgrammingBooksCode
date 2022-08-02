#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

int main( )
{
  date_duration dd = date(2000, 1, 1) - date(1900, 1, 1);
  cout << "The twentieth century had " << dd.days( ) << " days" << endl;
  dd = date(2100, 1, 1) - date(2000, 1, 1);
  cout << "The twenty-first century will have " << dd.days( ) << " days" << endl;
}
