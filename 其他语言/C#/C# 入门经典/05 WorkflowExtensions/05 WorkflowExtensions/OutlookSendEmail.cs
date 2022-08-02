using System;
using SharedInterfaces;
using Microsoft.Office.Interop.Outlook;

namespace _05_WorkflowExtensions
{
    public class OutlookSendEmail : ISendEmail
    {
        public void SendEmail(string sender, string recipient, string subject, string body)
        {
            Application app = new Application();
            var mapi = app.GetNamespace("MAPI");
            mapi.Logon(ShowDialog: false, NewSession: false);
            var outbox = mapi.GetDefaultFolder(OlDefaultFolders.olFolderOutbox);

            MailItem email = app.CreateItem(OlItemType.olMailItem);
            email.To = recipient;
            email.Subject = subject;
            email.Body = body;
            email.Send();
        }
    }
}
