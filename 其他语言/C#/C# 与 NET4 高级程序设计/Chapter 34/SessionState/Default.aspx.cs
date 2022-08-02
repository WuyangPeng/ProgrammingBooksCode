using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnSubmit_Click(object sender, EventArgs e)
    {
        // Set current user prefs.
        UserShoppingCart u =
             (UserShoppingCart)Session["UserShoppingCartInfo"];
        u.dateOfPickUp = myCalendar.SelectedDate;
        u.desiredCar = txtCarMake.Text;
        u.desiredCarColor = txtCarColor.Text;
        u.downPayment = float.Parse(txtDownPayment.Text);
        u.isLeasing = chkIsLeasing.Checked;
        lblUserInfo.Text = u.ToString();
        Session["UserShoppingCartInfo"] = u;

        lblUserID.Text = string.Format("Here is your ID: {0}",
            Session.SessionID);

    }
}