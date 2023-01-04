package com.tcre.weather.persistence;

import com.tcre.weather.wmsdata.HiLoData;
import com.tcre.weather.wmsdata.NoSuchDateException;
import java.util.Date;

public class DataToolkit implements com.tcre.weather.wmsdata.DataToolkit
{
  final private String temperatureKey = "Temp";

  public HiLoData getTempHiLoData(Date aDate) throws NoSuchDateException
  {
    return new HiLoProxy(temperatureKey, aDate);
  }

  public HiLoData getTempHiLoData(Date aDate, double initialValue) 
  {
    return new HiLoProxy(temperatureKey, aDate, initialValue);
  }
}
