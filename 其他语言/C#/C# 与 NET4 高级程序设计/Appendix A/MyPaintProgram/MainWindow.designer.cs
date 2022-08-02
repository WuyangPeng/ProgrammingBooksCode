namespace MyPaintProgram
{
  partial class MainWindow
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
        this.menuStrip1 = new System.Windows.Forms.MenuStrip();
        this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
        this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.pickShapeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.pickColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.clearSurfaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.menuStrip1.SuspendLayout();
        this.SuspendLayout();
        // 
        // menuStrip1
        // 
        this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolsToolStripMenuItem});
        this.menuStrip1.Location = new System.Drawing.Point(0, 0);
        this.menuStrip1.Name = "menuStrip1";
        this.menuStrip1.Size = new System.Drawing.Size(284, 24);
        this.menuStrip1.TabIndex = 0;
        this.menuStrip1.Text = "menuStrip1";
        // 
        // fileToolStripMenuItem
        // 
        this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
        this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
        this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
        this.fileToolStripMenuItem.Text = "&File";
        // 
        // saveToolStripMenuItem
        // 
        this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
        this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.saveToolStripMenuItem.Text = "&Save...";
        this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
        // 
        // loadToolStripMenuItem
        // 
        this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
        this.loadToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.loadToolStripMenuItem.Text = "&Load...";
        this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
        // 
        // toolStripSeparator1
        // 
        this.toolStripSeparator1.Name = "toolStripSeparator1";
        this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
        // 
        // exitToolStripMenuItem
        // 
        this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.exitToolStripMenuItem.Text = "E&xit";
        this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
        // 
        // pickShapeToolStripMenuItem
        // 
        this.pickShapeToolStripMenuItem.Name = "pickShapeToolStripMenuItem";
        this.pickShapeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.pickShapeToolStripMenuItem.Text = "Pick &Shape...";
        this.pickShapeToolStripMenuItem.Click += new System.EventHandler(this.pickShapeToolStripMenuItem_Click);
        // 
        // pickColorToolStripMenuItem
        // 
        this.pickColorToolStripMenuItem.Name = "pickColorToolStripMenuItem";
        this.pickColorToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.pickColorToolStripMenuItem.Text = "Pick Color...";
        this.pickColorToolStripMenuItem.Click += new System.EventHandler(this.pickColorToolStripMenuItem_Click);
        // 
        // clearSurfaceToolStripMenuItem
        // 
        this.clearSurfaceToolStripMenuItem.Name = "clearSurfaceToolStripMenuItem";
        this.clearSurfaceToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.clearSurfaceToolStripMenuItem.Text = "Clear Surface";
        this.clearSurfaceToolStripMenuItem.Click += new System.EventHandler(this.clearSurfaceToolStripMenuItem_Click);
        // 
        // toolsToolStripMenuItem
        // 
        this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pickShapeToolStripMenuItem,
            this.pickColorToolStripMenuItem,
            this.clearSurfaceToolStripMenuItem});
        this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
        this.toolsToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
        this.toolsToolStripMenuItem.Text = "&Tools";
        // 
        // MainWindow
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(284, 264);
        this.Controls.Add(this.menuStrip1);
        this.MainMenuStrip = this.menuStrip1;
        this.Name = "MainWindow";
        this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
        this.Text = "My Painting Program";
        this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainWindow_Paint);
        this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.MainWindow_MouseClick);
        this.menuStrip1.ResumeLayout(false);
        this.menuStrip1.PerformLayout();
        this.ResumeLayout(false);
        this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem pickShapeToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem pickColorToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem clearSurfaceToolStripMenuItem;
  }
}

