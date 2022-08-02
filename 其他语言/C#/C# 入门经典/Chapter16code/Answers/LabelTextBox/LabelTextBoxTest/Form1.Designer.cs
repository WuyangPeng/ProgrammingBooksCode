namespace LabelTextBoxTest
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
      this.buttonToggle = new System.Windows.Forms.Button();
      this.ctlLabelTextbox1 = new LabelTextBox.ctlLabelTextbox();
      this.SuspendLayout();
      // 
      // buttonToggle
      // 
      this.buttonToggle.Location = new System.Drawing.Point(108, 56);
      this.buttonToggle.Name = "buttonToggle";
      this.buttonToggle.Size = new System.Drawing.Size(75, 23);
      this.buttonToggle.TabIndex = 1;
      this.buttonToggle.Text = "Toggle";
      this.buttonToggle.UseVisualStyleBackColor = true;
      this.buttonToggle.Click += new System.EventHandler(this.buttonToggle_Click);
      // 
      // ctlLabelTextbox1
      // 
      this.ctlLabelTextbox1.LabelText = "";
      this.ctlLabelTextbox1.Location = new System.Drawing.Point(47, 13);
      this.ctlLabelTextbox1.MaxLength = 2;
      this.ctlLabelTextbox1.Name = "ctlLabelTextbox1";
      this.ctlLabelTextbox1.Position = LabelTextBox.ctlLabelTextbox.PositionEnum.Right;
      this.ctlLabelTextbox1.Size = new System.Drawing.Size(150, 20);
      this.ctlLabelTextbox1.TabIndex = 2;
      this.ctlLabelTextbox1.TextboxMargin = 0;
      this.ctlLabelTextbox1.TextboxText = "";
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(289, 88);
      this.Controls.Add(this.ctlLabelTextbox1);
      this.Controls.Add(this.buttonToggle);
      this.Name = "Form1";
      this.Text = "Form1";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button buttonToggle;
    private LabelTextBox.ctlLabelTextbox ctlLabelTextbox1;





  }
}

