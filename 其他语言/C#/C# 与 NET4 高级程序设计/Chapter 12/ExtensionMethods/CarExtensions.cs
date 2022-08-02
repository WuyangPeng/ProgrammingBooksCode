using System;
using System.Collections.Generic;
using System.Text;

namespace MyExtensionMethods 
{
  public class Car
  {
    public int Speed;
    public int SpeedUp()
    {
      return ++Speed;
    }
  }

  public static class CarExtensions
  {
    public static int SlowDown(this Car c)
    {
      return --c.Speed;
    }
  }
}
