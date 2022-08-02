using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CarOrderApp
{
  public partial class MainWindow : Form
  {
    public MainWindow()
    {
      InitializeComponent();
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e)
    {
        Close();
    }

    private void orderAutomobileToolStripMenuItem_Click(object sender, EventArgs e)
    {
      // Create your dialog object.
      ImageOrderAutoDialog dlg = new ImageOrderAutoDialog();

      // Show as modal dialog, and figure out which button 
      // they clicked on using the DialogResult return value.
      if (dlg.ShowDialog() == DialogResult.OK)
      {
        // Get values in each text box?
        string orderInfo = string.Format("Make: {0}, Color: {1}, Cost: {2}",
          dlg.txtMake.Text, dlg.txtColor.Text, dlg.txtPrice.Text);
        MessageBox.Show(orderInfo, "Information about your order!");
      }
    }
  }
}