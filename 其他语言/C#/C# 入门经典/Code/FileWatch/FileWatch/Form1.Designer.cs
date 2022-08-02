namespace FileWatch
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components;

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
            this.txtLocation = new System.Windows.Forms.TextBox();
            this.cmdBrowse = new System.Windows.Forms.Button();
            this.cmdWatch = new System.Windows.Forms.Button();
            this.lblWatch = new System.Windows.Forms.Label();
            this.FileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // txtLocation
            // 
            this.txtLocation.Location = new System.Drawing.Point(8, 26);
            this.txtLocation.Name = "txtLocation";
            this.txtLocation.Size = new System.Drawing.Size(184, 20);
            this.txtLocation.TabIndex = 0;
            // 
            // cmdBrowse
            // 
            this.cmdBrowse.Location = new System.Drawing.Point(208, 24);
            this.cmdBrowse.Name = "cmdBrowse";
            this.cmdBrowse.Size = new System.Drawing.Size(64, 24);
            this.cmdBrowse.TabIndex = 1;
            this.cmdBrowse.Text = "Browse...";
            this.cmdBrowse.UseVisualStyleBackColor = true;
            this.cmdBrowse.Click += new System.EventHandler(this.cmdBrowse_Click);
            // 
            // cmdWatch
            // 
            this.cmdWatch.Enabled = false;
            this.cmdWatch.Location = new System.Drawing.Point(88, 56);
            this.cmdWatch.Name = "cmdWatch";
            this.cmdWatch.Size = new System.Drawing.Size(80, 32);
            this.cmdWatch.TabIndex = 2;
            this.cmdWatch.Text = "Watch!";
            this.cmdWatch.UseVisualStyleBackColor = true;
            this.cmdWatch.Click += new System.EventHandler(this.cmdWatch_Click);
            // 
            // lblWatch
            // 
            this.lblWatch.AutoSize = true;
            this.lblWatch.Location = new System.Drawing.Point(8, 104);
            this.lblWatch.Name = "lblWatch";
            this.lblWatch.Size = new System.Drawing.Size(0, 13);
            this.lblWatch.TabIndex = 3;
            // 
            // FileDialog
            // 
            this.FileDialog.FileName = "openFileDialog1";
            this.FileDialog.Filter = "All Files|*.*";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 135);
            this.Controls.Add(this.lblWatch);
            this.Controls.Add(this.cmdWatch);
            this.Controls.Add(this.cmdBrowse);
            this.Controls.Add(this.txtLocation);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "File Monitor";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtLocation;
        private System.Windows.Forms.Button cmdBrowse;
        private System.Windows.Forms.Button cmdWatch;
        private System.Windows.Forms.Label lblWatch;
        private System.Windows.Forms.OpenFileDialog FileDialog;
    }
}

