package com.tcre.weather.persistence;

public class Scope
{
  public static void init()
  {
    com.tcre.weather.wmsdata.Scope.itsDataToolkit = new DataToolkit();
  }
}
