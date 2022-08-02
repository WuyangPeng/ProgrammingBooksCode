using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

/// <summary>
/// Summary description for UserShopptingCart
/// </summary>
public class UserShoppingCart
{
    public string desiredCar;
    public string desiredCarColor;
    public float downPayment;
    public bool isLeasing;
    public DateTime dateOfPickUp;
    public override string ToString()
    {
        return string.Format
         ("Car: {0}<br>Color: {1}<br>$ Down: {2}<br>Lease: {3}<br>Pick-up Date: {4}",
       desiredCar, desiredCarColor, downPayment, isLeasing,
       dateOfPickUp.ToShortDateString());
    }
}
