using System;
using System.Linq;
using System.Activities;
using System.Activities.Statements;
using System.Threading;

namespace _05_WorkflowExtensions
{

    class Program
    {
        static void Main(string[] args)
        {
            WorkflowApplication app = new WorkflowApplication(new Workflow1());
            app.OnUnhandledException = (e) =>
                {
                    return UnhandledExceptionAction.Abort;
                };

            app.Extensions.Add(new ConsoleSendEmail());
//            app.Extensions.Add(new LocalhostSender());
//            app.Extensions.Add(new OutlookSendEmail());

            ManualResetEvent finished = new ManualResetEvent(false);
            app.Completed = (completedArgs) => { finished.Set(); };
            app.Aborted = (abortedEventArgs) =>
                {
                    Console.WriteLine("Workflow Aborted.\r\n{0}",abortedEventArgs.Reason);
                    finished.Set();
                };

            app.Run();

            finished.WaitOne();
        }
    }
}
