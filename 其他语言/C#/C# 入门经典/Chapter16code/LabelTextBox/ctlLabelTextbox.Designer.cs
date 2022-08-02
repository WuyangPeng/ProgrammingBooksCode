namespace LabelTextBox
{
  partial class ctlLabelTextbox
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

    #region Component Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.labelCaption = new System.Windows.Forms.Label();
      this.textBoxText = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // labelCaption
      // 
      this.labelCaption.AutoSize = true;
      this.labelCaption.Location = new System.Drawing.Point(0, 0);
      this.labelCaption.Name = "labelCaption";
      this.labelCaption.Size = new System.Drawing.Size(29, 13);
      this.labelCaption.TabIndex = 0;
      this.labelCaption.Text = "label";
      // 
      // textBoxText
      // 
      this.textBoxText.Location = new System.Drawing.Point(8, 8);
      this.textBoxText.Name = "textBoxText";
      this.textBoxText.Size = new System.Drawing.Size(100, 20);
      this.textBoxText.TabIndex = 1;
      this.textBoxText.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxText_KeyDown);
      this.textBoxText.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxText_KeyPress);
      this.textBoxText.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBoxText_KeyUp);
      // 
      // ctlLabelTextbox
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add(this.textBoxText);
      this.Controls.Add(this.labelCaption);
      this.Name = "ctlLabelTextbox";
      this.Load += new System.EventHandler(this.ctlLabelTextbox_Load);
      this.SizeChanged += new System.EventHandler(this.ctlLabelTextbox_SizeChanged);
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label labelCaption;
    private System.Windows.Forms.TextBox textBoxText;
  }
}
