package com.tcre.weather.test;

import com.tcre.weather.api.ClockListener;

public class AlarmClockImp implements com.tcre.weather.api.AlarmClockImp
{
  public void register(ClockListener aListener)
  {
    new Timer(10, aListener).start();
  }
}
