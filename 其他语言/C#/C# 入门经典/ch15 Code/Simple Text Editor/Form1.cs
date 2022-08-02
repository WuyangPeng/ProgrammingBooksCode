using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Simple_Text_Editor
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void buttonBold_Click(object sender, EventArgs e)
    {
      Font oldFont;
      Font newFont;

      // Get the font that is being used in the selected text
      oldFont = this.richTextBoxText.SelectionFont;

      // If the font is using bold style now, we should remove the
      // Formatting.
      if (oldFont.Bold)
        newFont = new Font(oldFont, oldFont.Style & ~FontStyle.Bold);
      else
        newFont = new Font(oldFont, oldFont.Style | FontStyle.Bold);

      // Insert the new font and return focus to the RichTextBox.
      this.richTextBoxText.SelectionFont = newFont;
      this.richTextBoxText.Focus();
    }

    private void buttonUnderline_Click(object sender, EventArgs e)
    {
      Font oldFont;
      Font newFont;

      // Get the font that is being used in the selected text.
      oldFont = this.richTextBoxText.SelectionFont;

      // If the font is using Underline style now, we should remove it.
      if (oldFont.Underline)
        newFont = new Font(oldFont, oldFont.Style & ~FontStyle.Underline);
      else
        newFont = new Font(oldFont, oldFont.Style | FontStyle.Underline);

      // Insert the new font.
      this.richTextBoxText.SelectionFont = newFont;
      this.richTextBoxText.Focus();
    }

    private void buttonItalic_Click(object sender, EventArgs e)
    {
      Font oldFont;
      Font newFont;

      // Get the font that is being used in the selected text.
      oldFont = this.richTextBoxText.SelectionFont;

      // If the font is using Italic style now, we should remove it.
      if (oldFont.Italic)
        newFont = new Font(oldFont, oldFont.Style & ~FontStyle.Italic);
      else
        newFont = new Font(oldFont, oldFont.Style | FontStyle.Italic);

      // Insert the new font.
      this.richTextBoxText.SelectionFont = newFont;
      this.richTextBoxText.Focus();
    }

    private void buttonCenter_Click(object sender, EventArgs e)
    {
      if (this.richTextBoxText.SelectionAlignment == HorizontalAlignment.Center)
        this.richTextBoxText.SelectionAlignment = HorizontalAlignment.Left;
      else
        this.richTextBoxText.SelectionAlignment = HorizontalAlignment.Center;
      this.richTextBoxText.Focus();
    }

    private void textBoxSize_KeyPress(object sender, KeyPressEventArgs e)
    {
      // Remove all characters that are not numbers, backspace, or enter.
      if ((e.KeyChar < 48 || e.KeyChar > 57) &&
                                             e.KeyChar != 8 && e.KeyChar != 13)
      {
        e.Handled = true;
      }
      else if (e.KeyChar == 13)
      {
        // Apply size if the user hits enter
        TextBox txt = (TextBox)sender;

        if (txt.Text.Length > 0)
          ApplyTextSize(txt.Text);
        e.Handled = true;
        this.richTextBoxText.Focus();
      }
    }

    private void textBoxSize_Validated(object sender, EventArgs e)
    {
      TextBox txt = (TextBox)sender;

      ApplyTextSize(txt.Text);
      this.richTextBoxText.Focus();
    }

    private void ApplyTextSize(string textSize)
    {
      // Convert the text to a float because we’ll be needing a float shortly.
      float newSize = Convert.ToSingle(textSize);
      FontFamily currentFontFamily;
      Font newFont;

      // Create a new font of the same family but with the new size.
      currentFontFamily = this.richTextBoxText.SelectionFont.FontFamily;
      newFont = new Font(currentFontFamily, newSize);

      // Set the font of the selected text to the new font.
      this.richTextBoxText.SelectionFont = newFont;
    }

    private void richTextBoxText_LinkClicked(object sender, LinkClickedEventArgs e)
    {
      System.Diagnostics.Process.Start(e.LinkText);
    }

    private void buttonLoad_Click(object sender, EventArgs e)
    {
      // Load the file into the RichTextBox.
      try
      {
        richTextBoxText.LoadFile("Test.rtf");
      }
      catch (System.IO.FileNotFoundException)
      {
        MessageBox.Show("No file to load yet");
      }
    }

    private void buttonSave_Click(object sender, EventArgs e)
    {
      // Save the text.
      try
      {
        richTextBoxText.SaveFile("Test.rtf");
      }
      catch (System.Exception err)
      {
        MessageBox.Show(err.Message);
      }
    }
  }
}
