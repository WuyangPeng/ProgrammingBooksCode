using System;
using System.Windows.Forms;
using CorLibDumper;
using System.Drawing;

namespace WinFormsClientApp
{
    // Application object.
    public static class Program
    {
        public static void Main()
        {
            Application.Run(new MainWindow());
        }
    }

    // Our simple Window.
    public class MainWindow : Form
    {
        private Button btnDumpToFile = new Button();
        private TextBox txtTypeName = new TextBox();

        public MainWindow()
        {
            // Config the UI.
            ConfigControls();
        }

        private void ConfigControls()
        {
            // Configure the Form.
            Text = "My Mono Win Forms App!";
            ClientSize = new System.Drawing.Size(366, 90);
            StartPosition = FormStartPosition.CenterScreen;
            AcceptButton = btnDumpToFile;

            // Configure the Button.
            btnDumpToFile.Text = "Dump";
            btnDumpToFile.Location = new System.Drawing.Point(13, 40);

            // Handle click event anonymously.
            btnDumpToFile.Click += delegate
            {
                if (TypeDumper.DumpTypeToFile(txtTypeName.Text))
                    MessageBox.Show(string.Format(
                      "Data saved into {0}.txt",
                      txtTypeName.Text));
                else
                    MessageBox.Show("Error!  Can't find that type...");
            };
            Controls.Add(btnDumpToFile);

            // Configure the TextBox.
            txtTypeName.Location = new System.Drawing.Point(13, 13);
            txtTypeName.Size = new System.Drawing.Size(341, 20);
            Controls.Add(txtTypeName);
        }
    }
}
