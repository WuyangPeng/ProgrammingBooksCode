using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SimpleVSWinFormsApp
{
    public partial class MainWindow : Form
    {
        private string lifeTimeInfo = string.Empty;

        public MainWindow()
        {
            InitializeComponent();
            CenterToScreen();

            // Handle various lifetime events.
            FormClosed += new FormClosedEventHandler(MainWindow_FormClosed);
            Load += new EventHandler(MainWindow_Load);
            FormClosing += new FormClosingEventHandler(MainWindow_FormClosing);
            Activated += new EventHandler(MainWindow_Activated);
            Deactivate += new EventHandler(MainWindow_Deactivate);

        }

        #region Event Handlers
        void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            lifeTimeInfo += "Closing event\n";

            // Show a message box with Yes and No buttons.
            DialogResult dr = MessageBox.Show("Do you REALLY want to close this app?",
              "Closing event!", MessageBoxButtons.YesNo);

            // Which button was clicked?
            if (dr == DialogResult.No)
                e.Cancel = true;
            else
                e.Cancel = false;
        }

        void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            lifeTimeInfo += "Closed event\n";
            MessageBox.Show(lifeTimeInfo);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Application.Exit();
            Close();       
        }

        private void MainWindow_Load(object sender, System.EventArgs e)
        {
            lifeTimeInfo += "Load event\n";
        }

        private void MainWindow_Activated(object sender, System.EventArgs e)
        {
            lifeTimeInfo += "Activate event\n";
        }

        private void MainWindow_Deactivate(object sender, System.EventArgs e)
        {
            lifeTimeInfo += "Deactivate event\n";
        }
        #endregion
    }
}
