using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;

namespace _03_ReturningArgs
{

    class Program
    {
        static void Main(string[] args)
        {
            WorkflowInvoker.Invoke(new Workflow1());
        }
    }
}
