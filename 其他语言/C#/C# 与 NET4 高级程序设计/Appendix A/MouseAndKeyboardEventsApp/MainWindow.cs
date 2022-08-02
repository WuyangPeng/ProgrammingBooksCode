using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MouseAndKeyboardEventsApp
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        #region Event handlers.
        private void MainWindow_MouseMove(object sender, MouseEventArgs e)
        {
            Text = string.Format("Mouse Position: {0}", e.Location);
        }

        private void MainWindow_MouseDown(object sender, MouseEventArgs e)
        {
            // Which mouse button was clicked?
            if (e.Button == MouseButtons.Left)
                MessageBox.Show("Left click!");
            if (e.Button == MouseButtons.Right)
                MessageBox.Show("Right click!");
            if (e.Button == MouseButtons.Middle)
                MessageBox.Show("Middle click!");
        }

        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            Text = string.Format("Key Pressed: {0} Modifiers: {1}",
              e.KeyCode.ToString(), e.Modifiers.ToString());
        }
        #endregion
    }
}
