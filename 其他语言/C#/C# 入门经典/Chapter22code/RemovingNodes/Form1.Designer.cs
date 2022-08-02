namespace LoopThroughXmlDocument
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
      this.textBoxResult = new System.Windows.Forms.TextBox();
      this.buttonLoopThroughDocument = new System.Windows.Forms.Button();
      this.buttonCreateNode = new System.Windows.Forms.Button();
      this.buttonDeleteNode = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // textBoxResult
      // 
      this.textBoxResult.Location = new System.Drawing.Point(12, 12);
      this.textBoxResult.Multiline = true;
      this.textBoxResult.Name = "textBoxResult";
      this.textBoxResult.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBoxResult.Size = new System.Drawing.Size(341, 240);
      this.textBoxResult.TabIndex = 0;
      // 
      // buttonLoopThroughDocument
      // 
      this.buttonLoopThroughDocument.Location = new System.Drawing.Point(359, 10);
      this.buttonLoopThroughDocument.Name = "buttonLoopThroughDocument";
      this.buttonLoopThroughDocument.Size = new System.Drawing.Size(75, 23);
      this.buttonLoopThroughDocument.TabIndex = 1;
      this.buttonLoopThroughDocument.Text = "Loop";
      this.buttonLoopThroughDocument.UseVisualStyleBackColor = true;
      this.buttonLoopThroughDocument.Click += new System.EventHandler(this.buttonLoopThroughDocument_Click);
      // 
      // buttonCreateNode
      // 
      this.buttonCreateNode.Location = new System.Drawing.Point(359, 39);
      this.buttonCreateNode.Name = "buttonCreateNode";
      this.buttonCreateNode.Size = new System.Drawing.Size(75, 23);
      this.buttonCreateNode.TabIndex = 2;
      this.buttonCreateNode.Text = "Insert";
      this.buttonCreateNode.UseVisualStyleBackColor = true;
      this.buttonCreateNode.Click += new System.EventHandler(this.buttonCreateNode_Click);
      // 
      // buttonDeleteNode
      // 
      this.buttonDeleteNode.Location = new System.Drawing.Point(359, 68);
      this.buttonDeleteNode.Name = "buttonDeleteNode";
      this.buttonDeleteNode.Size = new System.Drawing.Size(75, 23);
      this.buttonDeleteNode.TabIndex = 3;
      this.buttonDeleteNode.Text = "Delete Node";
      this.buttonDeleteNode.UseVisualStyleBackColor = true;
      this.buttonDeleteNode.Click += new System.EventHandler(this.buttonDeleteNode_Click);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(217)))), ((int)(((byte)(217)))), ((int)(((byte)(217)))));
      this.ClientSize = new System.Drawing.Size(446, 264);
      this.Controls.Add(this.buttonDeleteNode);
      this.Controls.Add(this.buttonCreateNode);
      this.Controls.Add(this.buttonLoopThroughDocument);
      this.Controls.Add(this.textBoxResult);
      this.Name = "Form1";
      this.Text = "XML Nodes";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.TextBox textBoxResult;
    private System.Windows.Forms.Button buttonLoopThroughDocument;
    private System.Windows.Forms.Button buttonCreateNode;
    private System.Windows.Forms.Button buttonDeleteNode;
  }
}

