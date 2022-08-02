using System;

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
        /// <param name="recipient"></param>
        /// <param name="subject"></param>
        /// <param name="body"></param>
        void SendEmail(string recipient, string subject, string body);
    }
}
