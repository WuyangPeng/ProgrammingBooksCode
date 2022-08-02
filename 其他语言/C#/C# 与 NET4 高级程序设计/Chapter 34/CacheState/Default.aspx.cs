using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

using System.Data.SqlClient;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            carsGridView.DataSource = (DataSet)Cache["AppDataSet"];
            carsGridView.DataBind();
        }
    }
    protected void btnAddCar_Click(object sender, EventArgs e)
    {
        // Update the Inventory table
        // and call RefreshGrid().
        SqlConnection cn = new SqlConnection();
        cn.ConnectionString =
             "User ID=sa;Pwd=;Initial Catalog=Cars;" +
             "Data Source=(local)";
        cn.Open();
        string sql;
        SqlCommand cmd;
        // Insert new Car.
        sql = string.Format
             ("INSERT INTO Inventory(CarID, Make, Color, PetName) VALUES" +
             "('{0}', '{1}', '{2}', '{3}')",
             txtCarID.Text, txtCarMake.Text,
             txtCarColor.Text, txtCarPetName.Text);
        cmd = new SqlCommand(sql, cn);
        cmd.ExecuteNonQuery();
        cn.Close();
        RefreshGrid();
    }
    private void RefreshGrid()
    {
        // Populate grid.
        SqlConnection cn = new SqlConnection();
        cn.ConnectionString =
             "User ID=sa;Pwd=;Initial Catalog=Cars;Data Source=(local)";
        cn.Open();
        SqlCommand cmd = new SqlCommand("Select * from Inventory", cn);
        carsGridView.DataSource = cmd.ExecuteReader();
        carsGridView.DataBind();
        cn.Close();
    }
}