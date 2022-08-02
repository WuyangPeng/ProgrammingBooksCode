using System;
using AirVehicles;

class Program
{
  static void Main()
  {
    Console.WriteLine("***** Multifile Assembly Client *****");
    Helicopter h  = new Helicopter();
    h.TakeOff();

    // This will load the *.netmodule on demand.
    Ufo u = new Ufo();
    u.AbductHuman();
    Console.ReadLine();
  }
}
