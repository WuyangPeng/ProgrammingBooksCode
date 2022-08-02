//  opover.cpp
//  C++ program illustrates operator overloading.
//  Program will overload the "+" operator so that
//  several angles, in the format degrees minutes seconds,
//  can be added directly.
//  Chris H. Pappas and William H. Murray, 2000
//

#include <strstrea>
#include <stdlib>
#include <string>
using namespace std;

class angle_value {
  int degrees,minutes,seconds;

  public:
  angle_value() {degrees=0,
                 minutes=0,
                 seconds=0;}  // constructor
  angle_value(char *);
  angle_value operator +(angle_value);
  char * info_display(void);
};

angle_value::angle_value(char *angle_sum)
{
  degrees=atoi(strtok(angle_sum,"ó"));
  minutes=atoi(strtok(0,"' "));
  seconds=atoi(strtok(0,"\""));
}

angle_value angle_value::operator+(angle_value angle_sum)
{
  angle_value ang;
  ang.seconds=(seconds+angle_sum.seconds)%60;
  ang.minutes=((seconds+angle_sum.seconds)/60+
              minutes+angle_sum.minutes)%60;
  ang.degrees=((seconds+angle_sum.seconds)/60+
              minutes+angle_sum.minutes)/60;
  ang.degrees+=degrees+angle_sum.degrees;
  return ang;
}

char * angle_value::info_display()
{
  char *ang[15];
  // strstream required for incore formatting
  ostrstream(*ang,sizeof(ang)) << degrees << "°"
                               << minutes << "' "
                               << seconds << "\""
                               << ends;
  return *ang;
}

main()
{
  angle_value angle1("37° 15' 56\"");   //make with alt?248
  angle_value angle2("10° 44' 44\"");
  angle_value angle3("75° 17' 59\"");
  angle_value angle4("130° 32' 54\""); 
  angle_value sum_of_angles;

  sum_of_angles=angle1+angle2+angle3+angle4;
  cout << "the sum of the angles is "
       << sum_of_angles.info_display() << endl;
  return (0);
}
