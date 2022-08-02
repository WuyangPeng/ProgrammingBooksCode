namespace MyPaintProgram
{
  partial class ShapePickerDialog
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
      this.btnCancel = new System.Windows.Forms.Button();
      this.btnOK = new System.Windows.Forms.Button();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.radioButtonRect = new System.Windows.Forms.RadioButton();
      this.radioButtonCircle = new System.Windows.Forms.RadioButton();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // btnCancel
      // 
      this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.btnCancel.Location = new System.Drawing.Point(326, 54);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new System.Drawing.Size(75, 23);
      this.btnCancel.TabIndex = 0;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      // 
      // btnOK
      // 
      this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.btnOK.Location = new System.Drawing.Point(245, 54);
      this.btnOK.Name = "btnOK";
      this.btnOK.Size = new System.Drawing.Size(75, 23);
      this.btnOK.TabIndex = 1;
      this.btnOK.Text = "OK";
      this.btnOK.UseVisualStyleBackColor = true;
      this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.radioButtonRect);
      this.groupBox1.Controls.Add(this.radioButtonCircle);
      this.groupBox1.Location = new System.Drawing.Point(13, 13);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(173, 64);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Select Shape";
      // 
      // radioButtonRect
      // 
      this.radioButtonRect.AutoSize = true;
      this.radioButtonRect.Location = new System.Drawing.Point(76, 29);
      this.radioButtonRect.Name = "radioButtonRect";
      this.radioButtonRect.Size = new System.Drawing.Size(74, 17);
      this.radioButtonRect.TabIndex = 1;
      this.radioButtonRect.TabStop = true;
      this.radioButtonRect.Text = "Rectangle";
      this.radioButtonRect.UseVisualStyleBackColor = true;
      // 
      // radioButtonCircle
      // 
      this.radioButtonCircle.AutoSize = true;
      this.radioButtonCircle.Location = new System.Drawing.Point(7, 29);
      this.radioButtonCircle.Name = "radioButtonCircle";
      this.radioButtonCircle.Size = new System.Drawing.Size(51, 17);
      this.radioButtonCircle.TabIndex = 0;
      this.radioButtonCircle.TabStop = true;
      this.radioButtonCircle.Text = "Circle";
      this.radioButtonCircle.UseVisualStyleBackColor = true;
      // 
      // ShapePickerDialog
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(413, 90);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.btnOK);
      this.Controls.Add(this.btnCancel);
      this.Name = "ShapePickerDialog";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "ShapePickerDialog";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button btnCancel;
    private System.Windows.Forms.Button btnOK;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.RadioButton radioButtonRect;
    private System.Windows.Forms.RadioButton radioButtonCircle;
  }
}