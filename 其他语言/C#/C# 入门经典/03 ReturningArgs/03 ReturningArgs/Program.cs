using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;
using System.Collections.Generic;

namespace _03_ReturningArgs
{

    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, object> parms = new Dictionary<string, object>();
            parms.Add("Person", "Morgan");

            foreach (KeyValuePair<string, object> kvp in WorkflowInvoker.Invoke(new Workflow1(), parms))
            {
                Console.WriteLine("{0} = {1}", kvp.Key, kvp.Value);
            }
        }
    }
}
