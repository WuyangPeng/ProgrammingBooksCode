using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

// For the binary formatter.
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

namespace MyPaintProgram
{
  public partial class MainWindow : Form
  {
    // Current shape / color to draw.
    private SelectedShape currentShape;
    private Color currentColor = Color.DarkBlue;

    // This maintains each ShapeData.
    private List<ShapeData> shapes = new List<ShapeData>();

    public MainWindow()
    {
      InitializeComponent();
    }

    #region Form events
    private void MainWindow_Paint(object sender, PaintEventArgs e)
    {
      // Get the Graphics type for this window.
      Graphics g = e.Graphics;

      // Render each shape in the selected color. 
      foreach (ShapeData s in shapes)
      {
        // Render a rectangle or circle 20 x 20 pixels in size
        // using the correct color. 
        if (s.ShapeType == SelectedShape.Rectangle)
          g.FillRectangle(new SolidBrush(s.Color), s.UpperLeftPoint.X, s.UpperLeftPoint.Y, 20, 20);
        else
          g.FillEllipse(new SolidBrush(s.Color), s.UpperLeftPoint.X, s.UpperLeftPoint.Y, 20, 20);
      }
    }

    private void MainWindow_MouseClick(object sender, MouseEventArgs e)
    {
      // Make a ShapeData type based on current user
      // selections.
      ShapeData sd = new ShapeData();
      sd.ShapeType = currentShape;
      sd.Color = currentColor;
      sd.UpperLeftPoint = new Point(e.X, e.Y);

      // Add to the List<T> and forse the form to repaint itself. 
      shapes.Add(sd);
      Invalidate();
    }
    #endregion

    #region File Menu handlers
    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      using (SaveFileDialog saveDlg = new SaveFileDialog())
      {
        // Configure the look and feel of the save dialog.
        saveDlg.InitialDirectory = ".";
        saveDlg.Filter = "Shape files (*.shapes)|*.shapes";
        saveDlg.RestoreDirectory = true;
        saveDlg.FileName = "MyShapes";

        // If they click the OK button, open the new
        // file and serialize the List<>.
        if (saveDlg.ShowDialog() == DialogResult.OK)
        {
          Stream myStream = saveDlg.OpenFile();
          if ((myStream != null))
          {
            // Save the shapes!
            BinaryFormatter myBinaryFormat = new BinaryFormatter();
            myBinaryFormat.Serialize(myStream, shapes);
            myStream.Close();
          }
        }
      }
    }

    private void loadToolStripMenuItem_Click(object sender, EventArgs e)
    {
      using (OpenFileDialog openDlg = new OpenFileDialog())
      {
        openDlg.InitialDirectory = ".";
        openDlg.Filter = "Shape files (*.shapes)|*.shapes";
        openDlg.RestoreDirectory = true;
        openDlg.FileName = "MyShapes";

        if (openDlg.ShowDialog() == DialogResult.OK)
        {
          Stream myStream = openDlg.OpenFile();
          if ((myStream != null))
          {
            // Get the shapes!
            BinaryFormatter myBinaryFormat = new BinaryFormatter();
            shapes = (List<ShapeData>)myBinaryFormat.Deserialize(myStream);
            myStream.Close();
            Invalidate();
          }
        }
      }
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e)
    {
        Close();
    }
    #endregion

    #region Tools Menu handlers
    private void pickShapeToolStripMenuItem_Click(object sender, EventArgs e)
    {
      ShapePickerDialog dlg = new ShapePickerDialog();
      if (DialogResult.OK == dlg.ShowDialog())
      {
        currentShape = dlg.SelectedShape;
      }
    }

    private void clearSurfaceToolStripMenuItem_Click(object sender, EventArgs e)
    {
      shapes.Clear();

      // This will fire the paint event.
      Invalidate();
    }
    private void pickColorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      ColorDialog dlg = new ColorDialog();

      if (dlg.ShowDialog() == DialogResult.OK)
      {
        currentColor = dlg.Color;
      }
    }    
    #endregion
  }
}