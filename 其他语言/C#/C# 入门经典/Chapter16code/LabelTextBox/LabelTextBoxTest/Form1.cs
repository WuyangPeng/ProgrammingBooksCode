using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LabelTextBoxTest
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }

    private void buttonToggle_Click(object sender, EventArgs e)
    {
      ctlLabelTextbox1.Position = ctlLabelTextbox1.Position ==
 LabelTextBox.ctlLabelTextbox.PositionEnum.Right ?
 LabelTextBox.ctlLabelTextbox.PositionEnum.Below :
 LabelTextBox.ctlLabelTextbox.PositionEnum.Right;

    }

    private void ctlLabelTextbox1_PositionChanged_1(object sender, EventArgs e)
    {
      MessageBox.Show("Changed");
    }
  }
}
