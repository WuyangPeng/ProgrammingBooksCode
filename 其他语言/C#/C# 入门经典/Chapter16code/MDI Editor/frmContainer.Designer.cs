namespace Manual_Menus
{
  partial class frmContainer
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
      this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.tileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.cascadeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // menuStrip1
      // 
      this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.windowToolStripMenuItem});
      this.menuStrip1.Location = new System.Drawing.Point(0, 0);
      this.menuStrip1.MdiWindowListItem = this.windowToolStripMenuItem;
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new System.Drawing.Size(284, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.exitToolStripMenuItem});
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
      this.fileToolStripMenuItem.Text = "&File";
      // 
      // newToolStripMenuItem
      // 
      this.newToolStripMenuItem.MergeAction = System.Windows.Forms.MergeAction.MatchOnly;
      this.newToolStripMenuItem.MergeIndex = 0;
      this.newToolStripMenuItem.Name = "newToolStripMenuItem";
      this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
      this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
      this.newToolStripMenuItem.Text = "&New";
      this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
      // 
      // openToolStripMenuItem
      // 
      this.openToolStripMenuItem.MergeAction = System.Windows.Forms.MergeAction.MatchOnly;
      this.openToolStripMenuItem.MergeIndex = 1;
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
      this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
      this.openToolStripMenuItem.Text = "&Open";
      // 
      // exitToolStripMenuItem
      // 
      this.exitToolStripMenuItem.MergeAction = System.Windows.Forms.MergeAction.MatchOnly;
      this.exitToolStripMenuItem.MergeIndex = 10;
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
      this.exitToolStripMenuItem.Text = "E&xit";
      // 
      // windowToolStripMenuItem
      // 
      this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tileToolStripMenuItem,
            this.cascadeToolStripMenuItem,
            this.toolStripMenuItem1});
      this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
      this.windowToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
      this.windowToolStripMenuItem.Text = "&Window";
      // 
      // tileToolStripMenuItem
      // 
      this.tileToolStripMenuItem.Name = "tileToolStripMenuItem";
      this.tileToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
      this.tileToolStripMenuItem.Text = "&Tile";
      this.tileToolStripMenuItem.Click += new System.EventHandler(this.tileToolStripMenuItem_Click);
      // 
      // cascadeToolStripMenuItem
      // 
      this.cascadeToolStripMenuItem.Name = "cascadeToolStripMenuItem";
      this.cascadeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
      this.cascadeToolStripMenuItem.Text = "&Cascade";
      this.cascadeToolStripMenuItem.Click += new System.EventHandler(this.cascadeToolStripMenuItem_Click);
      // 
      // toolStripMenuItem1
      // 
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
      // 
      // frmContainer
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(284, 264);
      this.Controls.Add(this.menuStrip1);
      this.IsMdiContainer = true;
      this.MainMenuStrip = this.menuStrip1;
      this.Name = "frmContainer";
      this.Text = "Simple Text Editor";
      this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.MenuStrip menuStrip1;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem tileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem cascadeToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
  }
}