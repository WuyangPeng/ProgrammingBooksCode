using System;
using SharedInterfaces;

namespace _05_WorkflowExtensions
{
    public class ConsoleSendEmail : ISendEmail
    {
        public void SendEmail(string sender, string recipient, string subject, string body)
        {
            Console.WriteLine("Email to:      {0}", recipient);
            Console.WriteLine("      from:    {0}", sender);
            Console.WriteLine("      subject: {0}", subject);
            Console.WriteLine("      body:    {0}", body);
        }
    }
}
