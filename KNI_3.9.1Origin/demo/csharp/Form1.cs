using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using KNInet;

namespace csharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private KNInet.Katana katana;
        private void initialize_Click(object sender, EventArgs e)
        {
            if (tbIpAddress.Text == "0")
            {
                //use COM port
                katana = new KNInet.Katana(comPort.Text, configurationFile.Text);
                calibrate.Enabled = true;
            }
            else
            {
                //use Socket connection:
                tbOutput.AppendText("Initializing Katana...\n");
                katana = new KNInet.Katana(tbIpAddress.Text, comPort.Text, configurationFile.Text);
                tbOutput.AppendText("Katana initialized\n");
                calibrate.Enabled = true;
            }
        }
        private void configurationFile_Click(object sender, EventArgs e)
        {
            openConfigFileDialog.ShowDialog();
        }
        private void calibrate_Click(object sender, EventArgs e)
        {
            tbOutput.AppendText("Calibrating Katana...\n");
            katana.calibrate();
            tbOutput.AppendText("...done with calibration\n");
        }

        private void openConfigFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            configurationFile.Text = openConfigFileDialog.FileName;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void configurationFile_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}