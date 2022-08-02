namespace CarOrderApp
{
  partial class ImageOrderAutoDialog
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
        this.pictureBox1 = new System.Windows.Forms.PictureBox();
        this.SuspendLayout();
        // 
        // pictureBox1
        // 
        this.pictureBox1.Image = global::CarOrderApp.Properties.Resources.Lemon1;
        this.pictureBox1.Location = new System.Drawing.Point(255, 12);
        this.pictureBox1.Name = "pictureBox1";
        this.pictureBox1.Size = new System.Drawing.Size(118, 86);
        this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
        this.pictureBox1.TabIndex = 8;
        this.pictureBox1.TabStop = false;
        // 
        // ImageOrderAutoDialog
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.ClientSize = new System.Drawing.Size(385, 156);
        this.Controls.Add(this.pictureBox1);
        this.Name = "ImageOrderAutoDialog";
        this.Controls.SetChildIndex(this.pictureBox1, 0);
        this.Controls.SetChildIndex(this.txtMake, 0);
        this.Controls.SetChildIndex(this.txtColor, 0);
        this.Controls.SetChildIndex(this.txtPrice, 0);
        this.ResumeLayout(false);
        this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.PictureBox pictureBox1;
  }
}
