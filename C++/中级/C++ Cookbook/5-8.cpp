#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::date_time;
using namespace boost::posix_time;

typedef local_adjustor<ptime, -5, us_dst> EasternTZ;
typedef local_adjustor<ptime, -7, no_dst> ArizonaTZ;

ptime NYtoAZ(ptime nytime) {
  ptime utctime = EasternTZ::local_to_utc(nytime);
  return ArizonaTZ::utc_to_local(utctime);
}

int main( )
{
   // May 1st 2004,
   boost::gregorian::date thedate(2004, 6, 1);
   ptime nytime(thedate, hours(19)); // 7 pm
   ptime aztime = NYtoAZ(nytime);
   cout << "On May 1st, 2004, when it was " << nytime.time_of_day( ).hours( );
   cout << ":00 in New York, it was " << aztime.time_of_day( ).hours( );
   cout << ":00 in Arizona " << endl;
}
