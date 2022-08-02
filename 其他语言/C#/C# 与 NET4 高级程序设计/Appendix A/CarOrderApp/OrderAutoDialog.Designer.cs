namespace CarOrderApp
{
  partial class OrderAutoDialog
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
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.txtMake = new System.Windows.Forms.TextBox();
      this.txtColor = new System.Windows.Forms.TextBox();
      this.txtPrice = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // btnCancel
      // 
      this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.btnCancel.Location = new System.Drawing.Point(298, 121);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new System.Drawing.Size(75, 23);
      this.btnCancel.TabIndex = 4;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      // 
      // btnOK
      // 
      this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.btnOK.Location = new System.Drawing.Point(217, 121);
      this.btnOK.Name = "btnOK";
      this.btnOK.Size = new System.Drawing.Size(75, 23);
      this.btnOK.TabIndex = 3;
      this.btnOK.Text = "OK";
      this.btnOK.UseVisualStyleBackColor = true;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(13, 13);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(34, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Make";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(13, 44);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(31, 13);
      this.label2.TabIndex = 6;
      this.label2.Text = "Color";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(13, 78);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(31, 13);
      this.label3.TabIndex = 7;
      this.label3.Text = "Price";
      // 
      // txtMake
      // 
      this.txtMake.Location = new System.Drawing.Point(81, 13);
      this.txtMake.Name = "txtMake";
      this.txtMake.Size = new System.Drawing.Size(153, 20);
      this.txtMake.TabIndex = 0;
      // 
      // txtColor
      // 
      this.txtColor.Location = new System.Drawing.Point(81, 44);
      this.txtColor.Name = "txtColor";
      this.txtColor.Size = new System.Drawing.Size(153, 20);
      this.txtColor.TabIndex = 1;
      // 
      // txtPrice
      // 
      this.txtPrice.Location = new System.Drawing.Point(81, 78);
      this.txtPrice.Name = "txtPrice";
      this.txtPrice.Size = new System.Drawing.Size(153, 20);
      this.txtPrice.TabIndex = 2;
      // 
      // OrderAutoDialog
      // 
      this.AcceptButton = this.btnOK;
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.btnCancel;
      this.ClientSize = new System.Drawing.Size(385, 156);
      this.Controls.Add(this.txtPrice);
      this.Controls.Add(this.txtColor);
      this.Controls.Add(this.txtMake);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.btnOK);
      this.Controls.Add(this.btnCancel);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "OrderAutoDialog";
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "OrderAutoDialog";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button btnCancel;
    private System.Windows.Forms.Button btnOK;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    public System.Windows.Forms.TextBox txtMake;
    public System.Windows.Forms.TextBox txtColor;
    public System.Windows.Forms.TextBox txtPrice;
  }
}