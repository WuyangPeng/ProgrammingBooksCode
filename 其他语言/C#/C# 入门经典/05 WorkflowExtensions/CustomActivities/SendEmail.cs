using System;
using System.Activities;
using SharedInterfaces;
using System.ComponentModel;

namespace CustomActivities
{
    [Designer("CustomActivities.Design.SendEmailDesigner, CustomActivities.Design")]
    public class SendEmail : NativeActivity
    {
        public InArgument<string> Sender { get; set; }

        [RequiredArgument]
        public InArgument<string> Recipient { get; set; }

        [RequiredArgument]
        public InArgument<string> Subject { get; set; }

        [RequiredArgument]
        public InArgument<string> Body { get; set; }

        protected override void Execute(NativeActivityContext context)
        {
            context.GetExtension<ISendEmail>().SendEmail(Sender.Get(context),Recipient.Get(context), Subject.Get(context), Body.Get(context));
        }
    }
}
