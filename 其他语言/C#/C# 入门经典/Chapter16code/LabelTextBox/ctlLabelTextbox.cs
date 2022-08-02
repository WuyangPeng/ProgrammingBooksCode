using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LabelTextBox
{
  public partial class ctlLabelTextbox : UserControl
  {
    public enum PositionEnum
    {
      Right,
      Below
    }

    private PositionEnum position = PositionEnum.Right;
    private int textboxMargin = 0;
    private string labelText = "";

    public event System.EventHandler PositionChanged;

    public ctlLabelTextbox()
    {
      InitializeComponent();

    }

    public PositionEnum Position
    {
      get { return position; }
      set
      {
        position = value;
        MoveControls();
        if (PositionChanged != null)
          PositionChanged(this, new EventArgs());
      }
    }
    public int TextboxMargin
    {
      get { return textboxMargin; }
      set
      {
        textboxMargin = value;
        MoveControls();
      }
    }
    public string LabelText
    {
      get { return labelText; }
      set
      {
        labelText = value;
        labelCaption.Text = labelText;
        MoveControls();
      }
    }

    public string TextboxText
    {
      get { return textBoxText.Text; }
      set
      {
        textBoxText.Text = value;
      }
    }


    private void ctlLabelTextbox_Load(object sender, EventArgs e)
    {
      Height = textBoxText.Height > labelCaption.Height ?
        textBoxText.Height : labelCaption.Height;
      MoveControls();
    }


    private void ctlLabelTextbox_SizeChanged(object sender, EventArgs e)
    {
      MoveControls();
    }

    private void MoveControls()
    {
      switch (position)
      {
        case PositionEnum.Below:
          textBoxText.Top = labelCaption.Bottom;
          textBoxText.Left = labelCaption.Left;
          textBoxText.Width = Width;
          Height = textBoxText.Height + labelCaption.Height;
          break;
        case PositionEnum.Right:
          textBoxText.Top = labelCaption.Top;
          if (textboxMargin == 0)
          {
            int width = Width - labelCaption.Width - 3;
            textBoxText.Left = labelCaption.Right + 3;
            textBoxText.Width = width;
          }
          else
          {
            textBoxText.Left = textboxMargin + labelCaption.Width;
            textBoxText.Width = Width - textBoxText.Left;
          }
          Height = textBoxText.Height > labelCaption.Height ?
                                  textBoxText.Height : labelCaption.Height;
          break;
      }
    }

    private void textBoxText_KeyDown(object sender, KeyEventArgs e)
    {
      OnKeyDown(e);
    }

    private void textBoxText_KeyPress(object sender, KeyPressEventArgs e)
    {
      OnKeyPress(e);
    }

    private void textBoxText_KeyUp(object sender, KeyEventArgs e)
    {
      OnKeyUp(e);
    }
  }
}
