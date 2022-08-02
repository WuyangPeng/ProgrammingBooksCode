using System;
using SharedInterfaces;
using System.Net.Mail;

namespace _05_WorkflowExtensions
{
    public class LocalhostSender : ISendEmail
    {
        public void SendEmail(string sender, string recipient, string subject, string body)
        {
            MailMessage message = new MailMessage();
            message.From = new MailAddress(sender);
            message.To.Add(new MailAddress(recipient));
            message.Subject = subject;
            message.Body = body;

            SmtpClient client = new SmtpClient("localhost");
            client.Send(message);
        }
    }
}
