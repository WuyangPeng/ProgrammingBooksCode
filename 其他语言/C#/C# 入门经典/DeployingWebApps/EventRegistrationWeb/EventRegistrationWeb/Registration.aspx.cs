using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace EventRegistrationWeb
{
    public partial class Registration : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        public RegistrationInfo RegistrationInfo
        {
            get
            {
                return new RegistrationInfo
                {
                    FirstName = textFirstName.Text,
                    LastName = textLastName.Text,
                    Email = textEmail.Text,
                    SelectedEvent = dropDownListEvents.SelectedValue
                };
            }
        }




        protected void buttonSubmit_Click(object sender, EventArgs e)
        {
            string selectedEvent = dropDownListEvents.SelectedValue;
            string firstName = textFirstName.Text;
            string lastName = textLastName.Text;
            string email = textEmail.Text;

            labelResult.Text = String.Format("{0} {1} selected the event {2}",
                  firstName, lastName, selectedEvent);
        }
    }
}