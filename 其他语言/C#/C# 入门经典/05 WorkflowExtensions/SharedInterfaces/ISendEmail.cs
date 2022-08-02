using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SharedInterfaces
{
    /// <summary>
    /// Interface used by the SendEmail activity to send an email
    /// </summary>
    public interface ISendEmail
    {
        /// <summary>
        /// Sends an email
        /// </summary>
        /// <param name="sender">The person sending the email</param>
        /// <param name="recipient">The recipient of the email</param>
        /// <param name="subject">The subject</param>
        /// <param name="body">The body</param>
        void SendEmail(string sender, string recipient, string subject, string body);
    }
}
