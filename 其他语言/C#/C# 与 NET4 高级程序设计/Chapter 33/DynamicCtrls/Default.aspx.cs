using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, System.EventArgs e)
    {
        ListControlsInPanel();
    }

    #region List controls in the Panel
    private void ListControlsInPanel()
    {
        string theInfo = "";
        theInfo = string.Format("<b>Does the panel have controls? {0} </b><br/>", myPanel.HasControls());
        
        // Get all controls in the panel.
        foreach (Control c in myPanel.Controls)
        {
            if (!object.ReferenceEquals(c.GetType(),
              typeof(System.Web.UI.LiteralControl)))
            {
                theInfo += "***************************<br/>";
                theInfo += string.Format("Control Name? {0} <br/>", c.ToString());
                theInfo += string.Format("ID? {0} <br>", c.ID);
                theInfo += string.Format("Control Visible? {0} <br/>", c.Visible);
                theInfo += string.Format("ViewState? {0} <br/>", c.EnableViewState);
            }
        }
        lblControlInfo.Text = theInfo;
    }
    #endregion

    #region Add / remove items to panel
    protected void btnClearPanel_Click(object sender, System.EventArgs e)
    {
        // Clear all content from the panel, then re-list items.
        myPanel.Controls.Clear();
        ListControlsInPanel();
    }

    protected void btnAddWidgets_Click(object sender, System.EventArgs e)
    {
        for (int i = 0; i < 3; i++)
        {
            // Assign a name so we can get
            // the text value out later
            // using the incoming form data.
            TextBox t = new TextBox();
            t.ID = string.Format("newTextBox{0}", i);
            myPanel.Controls.Add(t);
            ListControlsInPanel();
        }
    }
    #endregion

    #region Get data in dynamic text boxes
    protected void btnGetTextData_Click(object sender, System.EventArgs e)
    {
        // Get teach text box by name.
        string lableData = string.Format("<li>{0}</li><br/>", 
            Request.Form.Get("newTextBox0"));
        lableData += string.Format("<li>{0}</li><br/>", 
            Request.Form.Get("newTextBox1"));
        lableData += string.Format("<li>{0}</li><br/>", 
            Request.Form.Get("newTextBox2"));
        lblTextBoxData.Text = lableData;
    }
    
    #endregion
}

