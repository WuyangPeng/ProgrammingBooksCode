package com.tcre.weather.system;

import java.util.Observer;
import java.util.Observable;

import com.tcre.weather.api.StationToolkit;

public class WeatherStation implements
        com.tcre.weather.component.WeatherStationComponent
{
  private TemperatureSensor itsTemperature;
  private BarometricPressureSensor itsPressure;
  private TempHiLo itsTempHiLo;

  public WeatherStation(String toolkit) throws Exception
  {
    Class classFor = Class.forName(toolkit);
    StationToolkit theToolkit = (StationToolkit)classFor.newInstance();
    com.tcre.weather.api.Scope.stationToolkit = theToolkit;

    AlarmClock itsClock = new AlarmClock(theToolkit);

    // create the sensors
    itsTemperature = new TemperatureSensor(theToolkit, itsClock);
    itsPressure = new BarometricPressureSensor(theToolkit, itsClock);

    // create the historical sensors
    itsTempHiLo = new TempHiLo(itsTemperature, itsClock);
  }

  public void addTempObserver(Observer o)
  {
    itsTemperature.addObserver(o);
  }

  public void addBPObserver(Observer o)
  {
    itsPressure.addObserver(o);
  }
}
