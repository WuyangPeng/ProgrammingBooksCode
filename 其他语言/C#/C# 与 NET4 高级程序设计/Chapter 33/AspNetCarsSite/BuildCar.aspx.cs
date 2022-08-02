using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;

public partial class BuildCarPage : System.Web.UI.Page
{
  protected void Page_Load(object sender, EventArgs e)
  {

  }
  protected void carWizard_FinishButtonClick(object sender, System.Web.UI.WebControls.WizardNavigationEventArgs e)
  {
    // Get each value.
    string order = string.Format("{0}, your {1} {2} will arrive on {3}.", 
      txtCarPetName.Text, ListBoxColors.SelectedValue, txtCarModel.Text, 
      carCalendar.SelectedDate.ToShortDateString());
    // Assign to label
    lblOrder.Text = order;
  }
}
