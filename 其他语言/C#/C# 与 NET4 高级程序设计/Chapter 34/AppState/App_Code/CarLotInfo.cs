using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public class CarLotInfo
{
    public CarLotInfo(string s, string c, string m)
    {
        salesPersonOfTheMonth = s;
        currentCarOnSale = c;
        mostPopularColorOnLot = m;
    }
    // Public for easy access.
    public string salesPersonOfTheMonth;
    public string currentCarOnSale;
    public string mostPopularColorOnLot;
}

