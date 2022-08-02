namespace Simple_Text_Editor
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
      this.buttonBold = new System.Windows.Forms.Button();
      this.buttonUnderline = new System.Windows.Forms.Button();
      this.buttonItalic = new System.Windows.Forms.Button();
      this.buttonCenter = new System.Windows.Forms.Button();
      this.buttonSave = new System.Windows.Forms.Button();
      this.buttonLoad = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.textBoxSize = new System.Windows.Forms.TextBox();
      this.richTextBoxText = new System.Windows.Forms.RichTextBox();
      this.SuspendLayout();
      // 
      // buttonBold
      // 
      this.buttonBold.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.buttonBold.Location = new System.Drawing.Point(92, 12);
      this.buttonBold.Name = "buttonBold";
      this.buttonBold.Size = new System.Drawing.Size(75, 23);
      this.buttonBold.TabIndex = 0;
      this.buttonBold.Text = "Bold";
      this.buttonBold.UseVisualStyleBackColor = true;
      this.buttonBold.Click += new System.EventHandler(this.buttonBold_Click);
      // 
      // buttonUnderline
      // 
      this.buttonUnderline.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.buttonUnderline.Location = new System.Drawing.Point(173, 12);
      this.buttonUnderline.Name = "buttonUnderline";
      this.buttonUnderline.Size = new System.Drawing.Size(75, 23);
      this.buttonUnderline.TabIndex = 1;
      this.buttonUnderline.Text = "Underline";
      this.buttonUnderline.UseVisualStyleBackColor = true;
      this.buttonUnderline.Click += new System.EventHandler(this.buttonUnderline_Click);
      // 
      // buttonItalic
      // 
      this.buttonItalic.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.buttonItalic.Location = new System.Drawing.Point(254, 12);
      this.buttonItalic.Name = "buttonItalic";
      this.buttonItalic.Size = new System.Drawing.Size(75, 23);
      this.buttonItalic.TabIndex = 2;
      this.buttonItalic.Text = "Italic";
      this.buttonItalic.UseVisualStyleBackColor = true;
      this.buttonItalic.Click += new System.EventHandler(this.buttonItalic_Click);
      // 
      // buttonCenter
      // 
      this.buttonCenter.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.buttonCenter.Location = new System.Drawing.Point(335, 12);
      this.buttonCenter.Name = "buttonCenter";
      this.buttonCenter.Size = new System.Drawing.Size(75, 23);
      this.buttonCenter.TabIndex = 3;
      this.buttonCenter.Text = "Center";
      this.buttonCenter.UseVisualStyleBackColor = true;
      this.buttonCenter.Click += new System.EventHandler(this.buttonCenter_Click);
      // 
      // buttonSave
      // 
      this.buttonSave.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.buttonSave.Location = new System.Drawing.Point(258, 229);
      this.buttonSave.Name = "buttonSave";
      this.buttonSave.Size = new System.Drawing.Size(75, 23);
      this.buttonSave.TabIndex = 4;
      this.buttonSave.Text = "Save";
      this.buttonSave.UseVisualStyleBackColor = true;
      this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
      // 
      // buttonLoad
      // 
      this.buttonLoad.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.buttonLoad.Location = new System.Drawing.Point(170, 229);
      this.buttonLoad.Name = "buttonLoad";
      this.buttonLoad.Size = new System.Drawing.Size(75, 23);
      this.buttonLoad.TabIndex = 5;
      this.buttonLoad.Text = "Load";
      this.buttonLoad.UseVisualStyleBackColor = true;
      this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
      // 
      // label1
      // 
      this.label1.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(209, 48);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(30, 13);
      this.label1.TabIndex = 6;
      this.label1.Text = "Size:";
      // 
      // textBoxSize
      // 
      this.textBoxSize.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.textBoxSize.Location = new System.Drawing.Point(245, 45);
      this.textBoxSize.Name = "textBoxSize";
      this.textBoxSize.Size = new System.Drawing.Size(49, 20);
      this.textBoxSize.TabIndex = 7;
      this.textBoxSize.Text = "10";
      this.textBoxSize.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxSize_KeyPress);
      this.textBoxSize.Validated += new System.EventHandler(this.textBoxSize_Validated);
      // 
      // richTextBoxText
      // 
      this.richTextBoxText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.richTextBoxText.Location = new System.Drawing.Point(12, 71);
      this.richTextBoxText.Name = "richTextBoxText";
      this.richTextBoxText.Size = new System.Drawing.Size(479, 152);
      this.richTextBoxText.TabIndex = 8;
      this.richTextBoxText.Text = "";
      this.richTextBoxText.LinkClicked += new System.Windows.Forms.LinkClickedEventHandler(this.richTextBoxText_LinkClicked);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
      this.ClientSize = new System.Drawing.Size(503, 264);
      this.Controls.Add(this.richTextBoxText);
      this.Controls.Add(this.textBoxSize);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.buttonLoad);
      this.Controls.Add(this.buttonSave);
      this.Controls.Add(this.buttonCenter);
      this.Controls.Add(this.buttonItalic);
      this.Controls.Add(this.buttonUnderline);
      this.Controls.Add(this.buttonBold);
      this.MinimumSize = new System.Drawing.Size(519, 300);
      this.Name = "Form1";
      this.Text = "Simple Text Editor";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonBold;
    private System.Windows.Forms.Button buttonUnderline;
    private System.Windows.Forms.Button buttonItalic;
    private System.Windows.Forms.Button buttonCenter;
    private System.Windows.Forms.Button buttonSave;
    private System.Windows.Forms.Button buttonLoad;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox textBoxSize;
    private System.Windows.Forms.RichTextBox richTextBoxText;
  }
}

