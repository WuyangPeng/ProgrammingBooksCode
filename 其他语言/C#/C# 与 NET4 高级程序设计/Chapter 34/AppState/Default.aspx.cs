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
    protected void btnShowAppVariables_Click(object sender, EventArgs e)
    {
        CarLotInfo appVars =
             ((CarLotInfo)Application["CarSiteInfo"]);
        string appState =
             string.Format("<li>Car on sale: {0}</li>",
             appVars.currentCarOnSale);
        appState +=
             string.Format("<li>Most popular color: {0}</li>",
             appVars.mostPopularColorOnLot);
        appState +=
             string.Format("<li>Big shot SalesPerson: {0}</li>",
             appVars.salesPersonOfTheMonth);
        lblAppVariables.Text = appState;

    }
    protected void btnSetNewSP_Click(object sender, EventArgs e)
    {
        // Set the new Salesperson.
        ((CarLotInfo)Application["CarSiteInfo"]).salesPersonOfTheMonth
             = txtNewSP.Text;
    }
}