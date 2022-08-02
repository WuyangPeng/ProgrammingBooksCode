using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var client = new WebServicesSample.SampleServiceSoapClient();
            // textBox2.Text = client.ReverseString(textBox1.Text);
            client.ReverseStringCompleted += client_ReverseStringCompleted;
            client.ReverseStringAsync(textBox1.Text);

        }

        void client_ReverseStringCompleted(object sender, WebServicesSample.ReverseStringCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                textBox2.Text = e.Result;
            }
            else
            {
                MessageBox.Show(e.Error.Message);
            }
        }
    }
}
