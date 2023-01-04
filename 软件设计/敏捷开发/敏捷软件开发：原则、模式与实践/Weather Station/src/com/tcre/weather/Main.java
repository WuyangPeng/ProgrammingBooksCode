package com.tcre.weather;

import java.util.Observer;
import java.util.Observable;

import com.tcre.weather.api.StationToolkit;
import com.tcre.weather.system.WeatherStation;
import com.tcre.weather.ui.MonitoringScreen;

class Main 
{
  public static void main(String[] args)
  {
    try
    {
      com.tcre.weather.persistence.Scope.init();

      WeatherStation ws = new WeatherStation(args[0]);
      MonitoringScreen ms = new MonitoringScreen(ws);
      for(;;) 
      {
        // loop forever
      }
    }
    catch(Exception e)
    {
      System.err.println(args[0] + " Invalid Toolkit");
    }
  }
}
