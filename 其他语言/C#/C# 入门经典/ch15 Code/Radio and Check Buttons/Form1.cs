using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TextBoxControls
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();

      this.buttonOK.Enabled = false;
    }

    private void buttonOK_Click(object sender, EventArgs e)
    {
      // No testing for invalid values are made, as that should
      // not be necessary

      string output;

      // Concatenate the text values of the four TextBoxes.
      output = "Name: " + textBoxName.Text + "\r\n";
      output += "Address: " + textBoxAddress.Text + "\r\n";
     output += "Occupation: " + (string)(checkBoxProgrammer.Checked ?
             "Programmer": "Not a programmer") + "\r\n";
     output += "Sex: " + (string)(radioButtonFemale.Checked ? "Female":
                                                           "Male") + "\r\n";
      output += "Age: " + textBoxAge.Text;

      // Insert the new text.
      textBoxOutput.Text = output;

    }

    private void buttonHelp_Click(object sender, EventArgs e)
    {
      // Write a short description of each TextBox in the Output TextBox.
      string output;

      output = "Name = Your name\r\n";
      output += "Address = Your address\r\n";
      output += "Programmer = Check ‘Programmer’ if you are a programmer\r\n";
      output += "Sex = Choose your sex\r\n";
      output += "Age = Your age";

      // Insert the new text.
      this.textBoxOutput.Text = output;
    }

    private void txtBoxEmpty_Validating(object sender, CancelEventArgs e)
    {
      // We know the sender is a TextBox, so we cast the sender object to that.
      TextBox tb = (TextBox)sender;

      // If the text is empty we set the background color of the
      // Textbox to red to indicate a problem. We use the tag value
      // of the control to indicate if the control contains valid
      // information.
      if (tb.Text.Length == 0)
      {
        tb.BackColor = Color.Red;

        // In this case we do not want to cancel further processing,
        // but if we had wanted to do this, we would have added this line:
        // e.Cancel = true;
      }
      else
      {
        tb.BackColor = System.Drawing.SystemColors.Window;
      }

      // Finally, we call ValidateOK which will set the value of
      // the OK button.
      ValidateOK();
    }

    private void ValidateOK()
    {
      // Set the OK button to enabled if all the Tags are true.
      this.buttonOK.Enabled = (textBoxName.BackColor != Color.Red &&
                               textBoxAddress.BackColor != Color.Red &&
                               textBoxAge.BackColor != Color.Red);
    }

    private void textBoxAge_KeyPress(object sender, KeyPressEventArgs e)
    {
      if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8)
        e.Handled = true; // Remove the character
    }
  }
}
