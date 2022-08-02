using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace LateBindingWithDynamic
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Dynamic Types*****");
            AddWithReflection();
            AddWithDynamic();
            Console.ReadLine();
        }

        #region Late binding with dynamic
        private static void AddWithDynamic()
        {
            Assembly asm = Assembly.Load("MathLibrary");

            try
            {
                // Get metadata for the SimpleMath type.
                Type math = asm.GetType("MathLibrary.SimpleMath");

                // Create a SimpleMath on the fly.
                dynamic obj = Activator.CreateInstance(math);
                Console.WriteLine("Result is: {0}", obj.Add(10, 70));
            }
            catch (Microsoft.CSharp.RuntimeBinder.RuntimeBinderException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        #endregion

        #region Late binding with reflection
        private static void AddWithReflection()
        {
            Assembly asm = Assembly.Load("MathLibrary");

            try
            {
                // Get metadata for the SimpleMath type.
                Type math = asm.GetType("MathLibrary.SimpleMath");

                // Create a SimpleMath on the fly.
                object obj = Activator.CreateInstance(math);

                // Get info for Add.
                MethodInfo mi = math.GetMethod("Add");

                // Invoke method (with parameters).
                object[] args = { 10, 70 };
                Console.WriteLine("Result is: {0}", mi.Invoke(obj, args));
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        #endregion
    }
}
