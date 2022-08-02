using System;
using System.Web.UI.WebControls;

namespace EventRegistrationWeb
{
    public partial class ResultsPage : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                if (!PreviousPage.IsValid)
                {
                    labelResult.Text = "Error in previous page";
                    return;
                }

                RegistrationInfo ri = PreviousPage.RegistrationInfo;

                labelResult.Text = String.Format("{0} {1} selected the event {2}",
                    ri.FirstName, ri.LastName, ri.SelectedEvent);


                //DropDownList dropDownListEvents =
                //   (DropDownList)PreviousPage.FindControl("dropDownListEvents");

                //string selectedEvent = dropDownListEvents.SelectedValue;

                //string firstName = ((TextBox)PreviousPage.FindControl("textFirstName")).Text;
                //string lastName = ((TextBox)PreviousPage.FindControl("textLastName")).Text;
                //string email = ((TextBox)PreviousPage.FindControl("textEmail")).Text;

                //labelResult.Text = String.Format("{0} {1} selected the event {2}",
                //      firstName, lastName, selectedEvent);
            }
            catch
            {
                labelResult.Text = "The originating page must contain " +
                      "textFirstName, textLastName, textEmail controls";
            }
        }
    }
}