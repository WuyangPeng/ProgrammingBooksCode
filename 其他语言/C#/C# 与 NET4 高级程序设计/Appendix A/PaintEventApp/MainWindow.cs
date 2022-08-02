using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace PaintEventApp
{
  public partial class MainWindow : Form
  {
    public MainWindow()
    {
      InitializeComponent();
    }

    private void MainWindow_Paint(object sender, PaintEventArgs e)
    {
      // Get the graphics object for this Form. 
      Graphics g = e.Graphics;

      // Draw a circle.
      g.FillEllipse(Brushes.Blue, 10, 20, 150, 80);

      // Draw a string in a custom font.
      g.DrawString("Hello GDI+", new Font("Times New Roman", 30),
                   Brushes.Red, 200, 200);
      
      // Draw a line with a custom pen.
      using (Pen p = new Pen(Color.YellowGreen, 10))
      {
        g.DrawLine(p, 80, 4, 200, 200);
      }
    }
  }
}