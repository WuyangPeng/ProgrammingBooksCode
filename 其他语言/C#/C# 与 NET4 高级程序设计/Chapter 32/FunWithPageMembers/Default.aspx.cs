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
    protected void btnGetBrowserStats_Click(object sender, EventArgs e)
    {
        string theInfo = "";
        theInfo += String.Format("<li>Is the client AOL? {0}",
             Request.Browser.AOL);
        theInfo +=
             String.Format("<li>Does the client support ActiveX? {0}",
             Request.Browser.ActiveXControls);
        theInfo += String.Format("<li>Is the client a Beta? {0}",
             Request.Browser.Beta);
        theInfo +=
             String.Format("<li>Dose the client support Java Applets? {0}",
             Request.Browser.JavaApplets);
        theInfo +=
             String.Format("<li>Does the client support Cookies? {0}",
             Request.Browser.Cookies);
        theInfo +=
             String.Format("<li>Does the client support VBScript? {0}",
             Request.Browser.VBScript);
        lblOutput.Text = theInfo;
    }

    protected void btnGetFormData_Click(object sender, EventArgs e)
    {
        // Get value for a widget with ID txtFirstName.
        // string firstName = Request.Form["txtFirstName"];

        // Better!
        string firstName = txtFirstName.Text;

        // Set this value on a Label.
        lblFormData.Text = firstName;
    }
    protected void btnHttpResponse_Click(object sender, EventArgs e)
    {
        Response.Write("<b>My name is:</b><br>");
        Response.Write(this.ToString());
        Response.Write("<br><br><b>Here was your last request:</b><br>");
        Response.WriteFile("MyHTMLPage.htm");
    }
    protected void btnWasteTime_Click(object sender, EventArgs e)
    {
        Response.Redirect("http://www.facebook.com");
    }
}