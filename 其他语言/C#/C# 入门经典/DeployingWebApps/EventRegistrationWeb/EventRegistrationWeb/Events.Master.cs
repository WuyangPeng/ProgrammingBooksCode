using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Security;

namespace EventRegistrationWeb
{
    public partial class Events : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //Control infoLabel = this.LoginView1.FindControl("Label1");
            //if (infoLabel != null)
            //    (infoLabel as Label).Text = "Welcome, " + Context.User.Identity.Name;
        }

        protected void OnLogout(object sender, EventArgs e)
        {
            FormsAuthentication.SignOut();
            FormsAuthentication.RedirectToLoginPage();
        }
    }
}