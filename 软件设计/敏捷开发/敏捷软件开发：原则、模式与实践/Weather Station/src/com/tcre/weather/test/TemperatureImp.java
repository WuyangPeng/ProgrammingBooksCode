package com.tcre.weather.test;

class TemperatureImp implements com.tcre.weather.api.TemperatureSensorImp
{
  private static int value = 0;

  public double read()
  {
    return ++value;
  }
}
