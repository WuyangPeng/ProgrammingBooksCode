// Soln4_4.cpp
/*
  I haved introduced a couple of manipulators for the stream output here
  that do not appear in the chapter.
  - std::fixed - specifies fixed point output for floating-point values.
  - std::setprecision(n) sets the number of decimal places for fixed precision out put as n.
     For the default floating-point notation it specifies the number of digits in the output value.
*/
#include <iostream>
#include <string>
#include <iomanip>

int main()
{
  double temperatures[] { 28.5, 27.0, 35.6, 47.9, 61.1, 65.4, 68.3, 75.0, 72.3, 56.2, 45.0, 42.1 };
  const double freezeF{ 32.0 };                                   // Water freezing point Fahrenheit
  const double boilF{ 212.0 };                                    // Water boiling point Fahrenheit
  const double boilC{ 100.0 };                                    // Water boiling point Centigrade

  double maxTempC{ -212.0 };                                      // Maximum temperature - impossibly low to start
  double minTempC{ 1000.0 };                                      // Minimum temperature - impossibly high to start
  double averageTempC{};                                          // Average temperature

  for (auto& temperature : temperatures)
  {
    temperature = (temperature - freezeF)*boilC/(boilF - freezeF);
    averageTempC += temperature;
    if(maxTempC < temperature) maxTempC = temperature;
    if(minTempC > temperature) minTempC = temperature;
  }
  std::cout << "The minimum temperature for the year in Centigrade was " 
            << std::fixed << std::setprecision(2)                 // Fixed point output - 2 decimal places
            << minTempC << " degrees." << std::endl; 

  std::cout << "The maximum temperature for the year in Centigrade was " 
            << std::fixed << std::setprecision(2)                 // Fixed point output - 2 decimal places
            << maxTempC << " degrees." << std::endl; 

  std::cout << "The average temperature for the year in Centigrade was " 
            << std::fixed << std::setprecision(2)                 // Fixed point output - 2 decimal places
            << averageTempC/_countof(temperatures) 
            << " degrees." << std::endl; 
}
