package com.tcre.weather.test;

import com.tcre.weather.api.ClockListener;

public class Timer extends Thread
{
  private ClockListener listener;
  private long delay;

  Timer(long aDelay, ClockListener alistener)
  {
    listener = alistener;
    delay = aDelay; // 10ms by convention
  }

  public void run()
  {
    try
    {
      for(;;) 
      {
        listener.tic();
        sleep(delay);
      }
    }
    catch (InterruptedException ie)
    {
      return;
    }
  }
}

  
