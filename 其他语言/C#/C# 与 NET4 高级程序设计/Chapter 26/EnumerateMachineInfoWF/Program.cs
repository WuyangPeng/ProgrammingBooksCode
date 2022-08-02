using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;
using System.Collections.Generic;

namespace EnumerateMachineInfoWF
{

    class Program
    {
        #region Look ma, no WF!
        //static void Main(string[] args)
        //{
        //    try
        //    {
        //        ExecuteBusinessProcess();
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine(ex.Message);
        //        Console.WriteLine(ex.Data["Reason"]);
        //    }   
        //}

        //private static void ExecuteBusinessProcess()
        //{
        //    string UserName = "Andrew";
        //    Console.WriteLine("Hello {0}", UserName);
        //    Console.WriteLine("Do you want me to list all machine drives?");

        //    string YesOrNo = Console.ReadLine();
        //    if (YesOrNo.ToUpper() == "Y")
        //    {
        //        Console.WriteLine("Wonderful!");
        //        string[] DriveNames = Environment.GetLogicalDrives();
        //        foreach (string item in DriveNames)
        //        {
        //            Console.WriteLine(item);
        //        }
        //        Console.WriteLine("Thanks for using this workflow");
        //    }
        //    else
        //    {
        //        Console.WriteLine("K, Bye...");
        //        Exception ex = new Exception("User Said No!");
        //        ex.Data["Reason"] = "YesOrNo was false";
        //    }
        //}
        #endregion

        static void Main(string[] args)
        {
            try
            {
                Dictionary<string, object> wfArgs = new Dictionary<string, object>();
                wfArgs.Add("UserName", "Andrew");

                WorkflowInvoker.Invoke(new Workflow1(), wfArgs);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.Data["Reason"]);
            }
        }
    }
}
