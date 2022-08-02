namespace Lists
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
      this.buttonMove = new System.Windows.Forms.Button();
      this.checkedListBoxPossibleValues = new System.Windows.Forms.CheckedListBox();
      this.listBoxSelected = new System.Windows.Forms.ListBox();
      this.SuspendLayout();
      // 
      // buttonMove
      // 
      this.buttonMove.Location = new System.Drawing.Point(196, 98);
      this.buttonMove.Name = "buttonMove";
      this.buttonMove.Size = new System.Drawing.Size(75, 23);
      this.buttonMove.TabIndex = 0;
      this.buttonMove.Text = "Move";
      this.buttonMove.UseVisualStyleBackColor = true;
      this.buttonMove.Click += new System.EventHandler(this.buttonMove_Click);
      // 
      // checkedListBoxPossibleValues
      // 
      this.checkedListBoxPossibleValues.CheckOnClick = true;
      this.checkedListBoxPossibleValues.FormattingEnabled = true;
      this.checkedListBoxPossibleValues.Items.AddRange(new object[] {
            "One",
            "Two",
            "Three",
            "Four",
            "Five",
            "Six",
            "Seven",
            "Eight",
            "Nine"});
      this.checkedListBoxPossibleValues.Location = new System.Drawing.Point(12, 12);
      this.checkedListBoxPossibleValues.Name = "checkedListBoxPossibleValues";
      this.checkedListBoxPossibleValues.Size = new System.Drawing.Size(178, 199);
      this.checkedListBoxPossibleValues.TabIndex = 1;
      // 
      // listBoxSelected
      // 
      this.listBoxSelected.FormattingEnabled = true;
      this.listBoxSelected.Location = new System.Drawing.Point(277, 15);
      this.listBoxSelected.Name = "listBoxSelected";
      this.listBoxSelected.Size = new System.Drawing.Size(178, 199);
      this.listBoxSelected.TabIndex = 2;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(467, 219);
      this.Controls.Add(this.listBoxSelected);
      this.Controls.Add(this.checkedListBoxPossibleValues);
      this.Controls.Add(this.buttonMove);
      this.Name = "Form1";
      this.Text = "Lists";
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Button buttonMove;
    private System.Windows.Forms.CheckedListBox checkedListBoxPossibleValues;
    private System.Windows.Forms.ListBox listBoxSelected;
  }
}

