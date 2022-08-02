using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MyPaintProgram
{
  // The two shapes which can be rendered by this 
  // application.
  public enum SelectedShape
  {
    Circle, Rectangle
  }

  public partial class ShapePickerDialog : Form
  {
    public SelectedShape SelectedShape { get; set; } 

    public ShapePickerDialog()
    {
      InitializeComponent();
    }

    private void btnOK_Click(object sender, EventArgs e)
    {
      if (radioButtonCircle.Checked)
        SelectedShape = SelectedShape.Circle;
      else
        SelectedShape = SelectedShape.Rectangle;
    }
  }
}