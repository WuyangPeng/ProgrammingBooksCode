using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Manual_Menus
{
  public partial class frmContainer : Form
  {
    private int counter;

    public frmContainer()
    {
      InitializeComponent();

      counter = 1;
      frmEditor newForm = new frmEditor(this, counter);
      newForm.Show();

    }

    private void newToolStripMenuItem_Click(object sender, EventArgs e)
    {
      frmEditor newForm = new frmEditor(this, ++counter);
      newForm.Show();
    }

    private void tileToolStripMenuItem_Click(object sender, EventArgs e)
    {
      LayoutMdi(MdiLayout.TileHorizontal);
    }

    private void cascadeToolStripMenuItem_Click(object sender, EventArgs e)
    {
      LayoutMdi(MdiLayout.Cascade);
    }
  }
}
