package com.tcre.weather.test;

import com.tcre.weather.api.*;

public class Toolkit implements StationToolkit
{
  private static AlarmClockImp itsClockImp = new com.tcre.weather.test.AlarmClockImp();
  private static PersistentImp itsPersistentImp = new PersistentImp();

  public com.tcre.weather.api.PersistentImp getPersistentImp()
  {
    return itsPersistentImp;
  }

  public com.tcre.weather.api.AlarmClockImp getAlarmClock()
  {
    return itsClockImp;
  }

  public com.tcre.weather.api.TemperatureSensorImp makeTemperature()
  {
    return new com.tcre.weather.test.TemperatureImp();
  }

  public com.tcre.weather.api.BarometricPressureSensorImp makeBarometricPressure()
  {
    return new com.tcre.weather.test.BarometricPressureImp();
  }
}

