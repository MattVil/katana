namespace csharp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.Label configurationFileLabel;
            System.Windows.Forms.Label comPortLabel;
            System.Windows.Forms.Label label1;
            this.configurationFile = new System.Windows.Forms.TextBox();
            this.initialize = new System.Windows.Forms.Button();
            this.calibrate = new System.Windows.Forms.Button();
            this.comPort = new System.Windows.Forms.NumericUpDown();
            this.openConfigFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.tbIpAddress = new System.Windows.Forms.TextBox();
            this.tbOutput = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            configurationFileLabel = new System.Windows.Forms.Label();
            comPortLabel = new System.Windows.Forms.Label();
            label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.comPort)).BeginInit();
            this.SuspendLayout();
            // 
            // configurationFileLabel
            // 
            configurationFileLabel.AutoSize = true;
            configurationFileLabel.Location = new System.Drawing.Point(13, 31);
            configurationFileLabel.Name = "configurationFileLabel";
            configurationFileLabel.Size = new System.Drawing.Size(91, 13);
            configurationFileLabel.TabIndex = 1;
            configurationFileLabel.Text = "Configuration-File:";
            // 
            // comPortLabel
            // 
            comPortLabel.AutoSize = true;
            comPortLabel.Location = new System.Drawing.Point(13, 70);
            comPortLabel.Name = "comPortLabel";
            comPortLabel.Size = new System.Drawing.Size(61, 13);
            comPortLabel.TabIndex = 2;
            comPortLabel.Text = "IP Address:";
            // 
            // configurationFile
            // 
            this.configurationFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.configurationFile.Location = new System.Drawing.Point(110, 28);
            this.configurationFile.Name = "configurationFile";
            this.configurationFile.Size = new System.Drawing.Size(116, 20);
            this.configurationFile.TabIndex = 0;
            this.configurationFile.Text = "configuration-file";
            this.configurationFile.Click += new System.EventHandler(this.configurationFile_Click);
            this.configurationFile.TextChanged += new System.EventHandler(this.configurationFile_TextChanged);
            // 
            // initialize
            // 
            this.initialize.Location = new System.Drawing.Point(12, 159);
            this.initialize.Name = "initialize";
            this.initialize.Size = new System.Drawing.Size(62, 23);
            this.initialize.TabIndex = 4;
            this.initialize.Text = "Initialize";
            this.initialize.UseVisualStyleBackColor = true;
            this.initialize.Click += new System.EventHandler(this.initialize_Click);
            // 
            // calibrate
            // 
            this.calibrate.Enabled = false;
            this.calibrate.Location = new System.Drawing.Point(89, 159);
            this.calibrate.Name = "calibrate";
            this.calibrate.Size = new System.Drawing.Size(68, 23);
            this.calibrate.TabIndex = 5;
            this.calibrate.Text = "Calibrate";
            this.calibrate.UseVisualStyleBackColor = true;
            this.calibrate.Click += new System.EventHandler(this.calibrate_Click);
            // 
            // comPort
            // 
            this.comPort.Location = new System.Drawing.Point(110, 100);
            this.comPort.Maximum = new decimal(new int[] {
            6000,
            0,
            0,
            0});
            this.comPort.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.comPort.Name = "comPort";
            this.comPort.Size = new System.Drawing.Size(116, 20);
            this.comPort.TabIndex = 6;
            this.comPort.Value = new decimal(new int[] {
            5566,
            0,
            0,
            0});
            // 
            // openConfigFileDialog
            // 
            this.openConfigFileDialog.FileName = "openFileDialog1";
            this.openConfigFileDialog.Filter = "Configuration-Files (*.cfg)|*.cfg";
            this.openConfigFileDialog.Title = "Select configuration-file";
            this.openConfigFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openConfigFileDialog_FileOk);
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(13, 102);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(26, 13);
            label1.TabIndex = 7;
            label1.Text = "Port";
            // 
            // tbIpAddress
            // 
            this.tbIpAddress.Location = new System.Drawing.Point(109, 67);
            this.tbIpAddress.Name = "tbIpAddress";
            this.tbIpAddress.Size = new System.Drawing.Size(116, 20);
            this.tbIpAddress.TabIndex = 8;
            this.tbIpAddress.Text = "192.168.168.232";
            // 
            // tbOutput
            // 
            this.tbOutput.Location = new System.Drawing.Point(12, 197);
            this.tbOutput.Multiline = true;
            this.tbOutput.Name = "tbOutput";
            this.tbOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbOutput.Size = new System.Drawing.Size(212, 96);
            this.tbOutput.TabIndex = 9;
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(158, 308);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(68, 23);
            this.btnClose.TabIndex = 10;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(238, 340);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.tbOutput);
            this.Controls.Add(this.tbIpAddress);
            this.Controls.Add(label1);
            this.Controls.Add(this.comPort);
            this.Controls.Add(this.calibrate);
            this.Controls.Add(this.initialize);
            this.Controls.Add(comPortLabel);
            this.Controls.Add(configurationFileLabel);
            this.Controls.Add(this.configurationFile);
            this.Name = "Form1";
            this.Text = "KNI .NET test";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.comPort)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button initialize;
        private System.Windows.Forms.Button calibrate;
        private System.Windows.Forms.TextBox configurationFile;
        private System.Windows.Forms.NumericUpDown comPort;
        private System.Windows.Forms.OpenFileDialog openConfigFileDialog;
        private System.Windows.Forms.TextBox tbIpAddress;
        private System.Windows.Forms.TextBox tbOutput;
        private System.Windows.Forms.Button btnClose;
    }
}

