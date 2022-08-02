using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;
using System.Collections.Generic;

namespace _02_ArgsAndVars
{

    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, object> parms = new Dictionary<string, object>();
            parms.Add("Name", "Morgan");
            
            WorkflowInvoker.Invoke(new Workflow1(), parms);
        }
    }
}
