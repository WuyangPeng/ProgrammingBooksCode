using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CarOrderApp
{
  public partial class OrderAutoDialog : Form
  {
    public OrderAutoDialog()
    {
      InitializeComponent();

      // When the Enter key is pressed, it is as if
      // the user clicked the btnOK button.
      this.AcceptButton = btnOK;
    }
  }
}