using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;
using CustomActivities;

namespace _04_CustomActivities
{

    class Program
    {
        static void Main(string[] args)
        {
            WorkflowInvoker.Invoke(new Workflow1());
        }
    }
}
