using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProcessMultipleExceptions
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Handling Multiple Exceptions *****\n");
            Car myCar = new Car("Rusty", 90);

            #region Try/catch logic
            try
            {
                // Trip Arg out of range exception.
                myCar.Accelerate(1000);
            }
            catch (CarIsDeadException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (ArgumentOutOfRangeException e)
            {
                Console.WriteLine(e.Message);
            }
            // This will catch any other exception
            // beyond CarIsDeadException or
            // ArgumentOutOfRangeException.
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                // This will always occur. Exception or not.
                myCar.CrankTunes(false);
            }
            #endregion

            Console.ReadLine();
        }
    }
}
