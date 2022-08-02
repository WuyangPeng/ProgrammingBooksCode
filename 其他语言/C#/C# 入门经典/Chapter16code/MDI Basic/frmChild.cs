using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MdiBasic
{
  public partial class frmChild : Form
  {
    public frmChild(frmContainer parent)
    {
      InitializeComponent();

      MdiParent = parent;
    }
  }
}
