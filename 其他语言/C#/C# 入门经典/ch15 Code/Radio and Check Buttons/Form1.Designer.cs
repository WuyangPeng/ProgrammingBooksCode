namespace TextBoxControls
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
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.textBoxName = new System.Windows.Forms.TextBox();
      this.textBoxAddress = new System.Windows.Forms.TextBox();
      this.textBoxOutput = new System.Windows.Forms.TextBox();
      this.textBoxAge = new System.Windows.Forms.TextBox();
      this.buttonOK = new System.Windows.Forms.Button();
      this.buttonHelp = new System.Windows.Forms.Button();
      this.checkBoxProgrammer = new System.Windows.Forms.CheckBox();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.radioButtonFemale = new System.Windows.Forms.RadioButton();
      this.radioButtonMale = new System.Windows.Forms.RadioButton();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(12, 224);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(26, 13);
      this.label1.TabIndex = 11;
      this.label1.Text = "Age";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(12, 17);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(35, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Name";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(12, 244);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(39, 13);
      this.label3.TabIndex = 1;
      this.label3.Text = "Output";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(12, 43);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(45, 13);
      this.label4.TabIndex = 9;
      this.label4.Text = "Address";
      // 
      // textBoxName
      // 
      this.textBoxName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxName.Location = new System.Drawing.Point(88, 14);
      this.textBoxName.Name = "textBoxName";
      this.textBoxName.Size = new System.Drawing.Size(326, 20);
      this.textBoxName.TabIndex = 0;
      this.textBoxName.Validating += new System.ComponentModel.CancelEventHandler(this.txtBoxEmpty_Validating);
      // 
      // textBoxAddress
      // 
      this.textBoxAddress.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxAddress.Location = new System.Drawing.Point(88, 40);
      this.textBoxAddress.Multiline = true;
      this.textBoxAddress.Name = "textBoxAddress";
      this.textBoxAddress.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxAddress.Size = new System.Drawing.Size(326, 81);
      this.textBoxAddress.TabIndex = 1;
      this.textBoxAddress.Validating += new System.ComponentModel.CancelEventHandler(this.txtBoxEmpty_Validating);
      // 
      // textBoxOutput
      // 
      this.textBoxOutput.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxOutput.Location = new System.Drawing.Point(15, 260);
      this.textBoxOutput.Multiline = true;
      this.textBoxOutput.Name = "textBoxOutput";
      this.textBoxOutput.ReadOnly = true;
      this.textBoxOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxOutput.Size = new System.Drawing.Size(399, 142);
      this.textBoxOutput.TabIndex = 4;
      // 
      // textBoxAge
      // 
      this.textBoxAge.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxAge.Location = new System.Drawing.Point(88, 221);
      this.textBoxAge.MaxLength = 3;
      this.textBoxAge.Name = "textBoxAge";
      this.textBoxAge.Size = new System.Drawing.Size(110, 20);
      this.textBoxAge.TabIndex = 3;
      this.textBoxAge.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxAge_KeyPress);
      this.textBoxAge.Validating += new System.ComponentModel.CancelEventHandler(this.txtBoxEmpty_Validating);
      // 
      // buttonOK
      // 
      this.buttonOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonOK.Location = new System.Drawing.Point(420, 12);
      this.buttonOK.Name = "buttonOK";
      this.buttonOK.Size = new System.Drawing.Size(75, 23);
      this.buttonOK.TabIndex = 5;
      this.buttonOK.Text = "OK";
      this.buttonOK.UseVisualStyleBackColor = true;
      this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
      // 
      // buttonHelp
      // 
      this.buttonHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonHelp.CausesValidation = false;
      this.buttonHelp.Location = new System.Drawing.Point(420, 41);
      this.buttonHelp.Name = "buttonHelp";
      this.buttonHelp.Size = new System.Drawing.Size(75, 23);
      this.buttonHelp.TabIndex = 6;
      this.buttonHelp.Text = "Help";
      this.buttonHelp.UseVisualStyleBackColor = true;
      this.buttonHelp.Click += new System.EventHandler(this.buttonHelp_Click);
      // 
      // checkBoxProgrammer
      // 
      this.checkBoxProgrammer.AutoSize = true;
      this.checkBoxProgrammer.Checked = true;
      this.checkBoxProgrammer.CheckState = System.Windows.Forms.CheckState.Checked;
      this.checkBoxProgrammer.Location = new System.Drawing.Point(15, 127);
      this.checkBoxProgrammer.Name = "checkBoxProgrammer";
      this.checkBoxProgrammer.Size = new System.Drawing.Size(82, 17);
      this.checkBoxProgrammer.TabIndex = 12;
      this.checkBoxProgrammer.Text = "Programmer";
      this.checkBoxProgrammer.UseVisualStyleBackColor = true;
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.radioButtonMale);
      this.groupBox1.Controls.Add(this.radioButtonFemale);
      this.groupBox1.Location = new System.Drawing.Point(15, 150);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(399, 65);
      this.groupBox1.TabIndex = 13;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Sex";
      // 
      // radioButtonFemale
      // 
      this.radioButtonFemale.AutoSize = true;
      this.radioButtonFemale.Checked = true;
      this.radioButtonFemale.Location = new System.Drawing.Point(78, 24);
      this.radioButtonFemale.Name = "radioButtonFemale";
      this.radioButtonFemale.Size = new System.Drawing.Size(59, 17);
      this.radioButtonFemale.TabIndex = 0;
      this.radioButtonFemale.TabStop = true;
      this.radioButtonFemale.Text = "Female";
      this.radioButtonFemale.UseVisualStyleBackColor = true;
      // 
      // radioButtonMale
      // 
      this.radioButtonMale.AutoSize = true;
      this.radioButtonMale.Location = new System.Drawing.Point(235, 24);
      this.radioButtonMale.Name = "radioButtonMale";
      this.radioButtonMale.Size = new System.Drawing.Size(48, 17);
      this.radioButtonMale.TabIndex = 1;
      this.radioButtonMale.Text = "Male";
      this.radioButtonMale.UseVisualStyleBackColor = true;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
      this.ClientSize = new System.Drawing.Size(507, 414);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.checkBoxProgrammer);
      this.Controls.Add(this.buttonHelp);
      this.Controls.Add(this.buttonOK);
      this.Controls.Add(this.textBoxAge);
      this.Controls.Add(this.textBoxOutput);
      this.Controls.Add(this.textBoxAddress);
      this.Controls.Add(this.textBoxName);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.MinimumSize = new System.Drawing.Size(513, 374);
      this.Name = "Form1";
      this.Text = "Radio Buttons and Check Boxes";
      this.Validating += new System.ComponentModel.CancelEventHandler(this.txtBoxEmpty_Validating);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.TextBox textBoxName;
    private System.Windows.Forms.TextBox textBoxAddress;
    private System.Windows.Forms.TextBox textBoxOutput;
    private System.Windows.Forms.TextBox textBoxAge;
    private System.Windows.Forms.Button buttonOK;
    private System.Windows.Forms.Button buttonHelp;
    private System.Windows.Forms.CheckBox checkBoxProgrammer;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.RadioButton radioButtonMale;
    private System.Windows.Forms.RadioButton radioButtonFemale;
  }
}

