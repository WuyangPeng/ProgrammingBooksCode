namespace ButtonDialog
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
      this.buttonEnglish = new System.Windows.Forms.Button();
      this.buttonDanish = new System.Windows.Forms.Button();
      this.buttonOK = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // buttonEnglish
      // 
      this.buttonEnglish.Image = global::ButtonDialog.Properties.Resources.UK;
      this.buttonEnglish.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
      this.buttonEnglish.Location = new System.Drawing.Point(12, 12);
      this.buttonEnglish.Name = "buttonEnglish";
      this.buttonEnglish.Size = new System.Drawing.Size(89, 23);
      this.buttonEnglish.TabIndex = 0;
      this.buttonEnglish.Text = "English";
      this.buttonEnglish.UseVisualStyleBackColor = true;
      this.buttonEnglish.Click += new System.EventHandler(this.buttonEnglish_Click);
      // 
      // buttonDanish
      // 
      this.buttonDanish.Image = global::ButtonDialog.Properties.Resources.DK;
      this.buttonDanish.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
      this.buttonDanish.Location = new System.Drawing.Point(140, 12);
      this.buttonDanish.Name = "buttonDanish";
      this.buttonDanish.Size = new System.Drawing.Size(89, 23);
      this.buttonDanish.TabIndex = 1;
      this.buttonDanish.Text = "Danish";
      this.buttonDanish.UseVisualStyleBackColor = true;
      this.buttonDanish.Click += new System.EventHandler(this.buttonDanish_Click);
      // 
      // buttonOK
      // 
      this.buttonOK.Location = new System.Drawing.Point(76, 41);
      this.buttonOK.Name = "buttonOK";
      this.buttonOK.Size = new System.Drawing.Size(89, 23);
      this.buttonOK.TabIndex = 2;
      this.buttonOK.Text = "OK";
      this.buttonOK.UseVisualStyleBackColor = true;
      this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(241, 74);
      this.Controls.Add(this.buttonOK);
      this.Controls.Add(this.buttonDanish);
      this.Controls.Add(this.buttonEnglish);
      this.Name = "Form1";
      this.Text = "Do you speak English?";
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button buttonEnglish;
    private System.Windows.Forms.Button buttonDanish;
    private System.Windows.Forms.Button buttonOK;
  }
}

