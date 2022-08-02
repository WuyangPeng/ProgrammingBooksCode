namespace XPathQuery
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
      this.buttonExecute = new System.Windows.Forms.Button();
      this.textBoxQuery = new System.Windows.Forms.TextBox();
      this.textBoxResult = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(12, 9);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(35, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Query";
      // 
      // buttonExecute
      // 
      this.buttonExecute.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.buttonExecute.Location = new System.Drawing.Point(415, 4);
      this.buttonExecute.Name = "buttonExecute";
      this.buttonExecute.Size = new System.Drawing.Size(75, 23);
      this.buttonExecute.TabIndex = 1;
      this.buttonExecute.Text = "Execute";
      this.buttonExecute.UseVisualStyleBackColor = true;
      this.buttonExecute.Click += new System.EventHandler(this.buttonExecute_Click);
      // 
      // textBoxQuery
      // 
      this.textBoxQuery.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxQuery.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.textBoxQuery.Location = new System.Drawing.Point(53, 6);
      this.textBoxQuery.Multiline = true;
      this.textBoxQuery.Name = "textBoxQuery";
      this.textBoxQuery.Size = new System.Drawing.Size(356, 58);
      this.textBoxQuery.TabIndex = 2;
      // 
      // textBoxResult
      // 
      this.textBoxResult.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBoxResult.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.textBoxResult.Location = new System.Drawing.Point(15, 70);
      this.textBoxResult.Multiline = true;
      this.textBoxResult.Name = "textBoxResult";
      this.textBoxResult.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxResult.Size = new System.Drawing.Size(475, 182);
      this.textBoxResult.TabIndex = 3;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(502, 264);
      this.Controls.Add(this.textBoxResult);
      this.Controls.Add(this.textBoxQuery);
      this.Controls.Add(this.buttonExecute);
      this.Controls.Add(this.label1);
      this.Name = "Form1";
      this.Text = "Form1";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button buttonExecute;
    private System.Windows.Forms.TextBox textBoxQuery;
    private System.Windows.Forms.TextBox textBoxResult;
  }
}

