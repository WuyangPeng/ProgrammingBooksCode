using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;

using System.Collections.Generic;
using System.Threading;

namespace FirstWorkflowExampleApp
{

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Welcome to this amazing WF application *****");
            
            // Get data from user, to pass to workflow. 
            Console.Write("Please enter the data to pass the workflow: ");
            string wfData = Console.ReadLine();

            // Package up the data as a dictionary. 
            Dictionary<string, object> wfArgs = new Dictionary<string,object>();
            wfArgs.Add("MessageToShow", wfData);

            AutoResetEvent waitHandle = new AutoResetEvent(false);

            // Pass to the workflow. 
            WorkflowApplication app = new WorkflowApplication(new Workflow1(), wfArgs);

            // Hook up an event with this app. 
            app.Completed = (completedArgs) => {
                waitHandle.Set(); 
                Console.WriteLine("The workflow is done!");
            };

            // Start the workflow! 
            app.Run();

            // Wait until we are notified the workflow is done.
            waitHandle.WaitOne();

            Console.WriteLine("Thanks for playing");
        }
    }
}
