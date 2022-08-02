using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace ListView
{
  public partial class Form1 : Form
  {
    private System.Collections.Specialized.StringCollection folderCol;

    public Form1()
    {
      InitializeComponent();

      // Init ListView and folder collection
      folderCol = new System.Collections.Specialized.StringCollection();
      CreateHeadersAndFillListView();
      PaintListView(@"C:\");
      folderCol.Add(@"C:\");

    }

    private void CreateHeadersAndFillListView()
    {
      ColumnHeader colHead;

      // First header
      colHead = new ColumnHeader();
      colHead.Text = "Filename";
      listViewFilesAndFolders.Columns.Add(colHead); // Insert the header

      // Second header
      colHead = new ColumnHeader();
      colHead.Text = "Size";
      listViewFilesAndFolders.Columns.Add(colHead); // Insert the header

      // Third header
      colHead = new ColumnHeader();
      colHead.Text = "Last accessed";
      listViewFilesAndFolders.Columns.Add(colHead); // Insert the header
    }

    private void PaintListView(string root)
    {
      try
      {
        // Two local variables that are used to create the items to insert
        ListViewItem lvi;
        ListViewItem.ListViewSubItem lvsi;

        // If there’s no root folder, we can’t insert anything.
        if (string.IsNullOrEmpty(root))
          return;

        // Get information about the root folder.
        DirectoryInfo dir = new DirectoryInfo(root);

        // Retrieve the files and folders from the root folder.
        DirectoryInfo[] dirs = dir.GetDirectories(); // Folders
        FileInfo[] files = dir.GetFiles();           // Files

        // Clear the ListView. Note that we call the Clear method on the
        // Items collection rather than on the ListView itself.
        // The Clear method of the ListView remove everything, including column
        // headers, and we only want to remove the items from the view.
        listViewFilesAndFolders.Items.Clear();

        // Set the label with the current path.
        labelCurrentPath.Text = root;

        // Lock the ListView for updates.
        listViewFilesAndFolders.BeginUpdate();


        // Loop through all folders in the root folder and insert them.
        foreach (DirectoryInfo di in dirs)
        {
          // Create the main ListViewItem.
          lvi = new ListViewItem();
          lvi.Text = di.Name; // Folder name
          lvi.ImageIndex = 0; // The folder icon has index 0
          lvi.Tag = di.FullName; // Set the tag to the qualified path of the
          // folder

          // Create the two ListViewSubItems.
          lvsi = new ListViewItem.ListViewSubItem();
          lvsi.Text = ""; // Size—a folder has no size and so this column
          // is empty
          lvi.SubItems.Add(lvsi); // Add the subitem to the ListViewItem

          lvsi = new ListViewItem.ListViewSubItem();
          lvsi.Text = di.LastAccessTime.ToString(); // Last accessed column
          lvi.SubItems.Add(lvsi); // Add the subitem to the ListViewItem.

          // Add the ListViewItem to the Items collection of the ListView.
          listViewFilesAndFolders.Items.Add(lvi);
        }

        // Loop through all the files in the root folder.
        foreach (FileInfo fi in files)
        {
          // Create the main ListViewItem.
          lvi = new ListViewItem();
          lvi.Text = fi.Name; // Filename
          lvi.ImageIndex = 1; // The icon we use to represent a folder has
          // index 1.
          lvi.Tag = fi.FullName; // Set the tag to the qualified path of the
          // file.

          // Create the two subitems.
          lvsi = new ListViewItem.ListViewSubItem();
          lvsi.Text = fi.Length.ToString(); // Length of the file
          lvi.SubItems.Add(lvsi); // Add to the SubItems collection

          lvsi = new ListViewItem.ListViewSubItem();
          lvsi.Text = fi.LastAccessTime.ToString(); // Last Accessed Column
          lvi.SubItems.Add(lvsi); // Add to the SubItems collection

          // Add the item to the Items collection of the ListView.
          listViewFilesAndFolders.Items.Add(lvi);
        }

        // Unlock the ListView. The items that have been inserted will now
        // be displayed.
        listViewFilesAndFolders.EndUpdate();
      }
      catch (System.Exception err)
      {
        MessageBox.Show("Error: " + err.Message);
      }
    }

    private void listViewFilesAndFolders_ItemActivate(object sender, EventArgs e)
    {
      // Cast the sender to a ListView and get the tag of the first selected
      // item.
      System.Windows.Forms.ListView lw = (System.Windows.Forms.ListView)sender;
      string filename = lw.SelectedItems[0].Tag.ToString();

      if (lw.SelectedItems[0].ImageIndex != 0)
      {
        try
        {
          // Attempt to run the file.
          System.Diagnostics.Process.Start(filename);
        }
        catch
        {
          // If the attempt fails we simply exit the method.
          return;
        }
      }
      else
      {
        // Insert the items.
        PaintListView(filename);
        folderCol.Add(filename);
      }
    }

    private void buttonBack_Click(object sender, EventArgs e)
    {
      if (folderCol.Count > 1)
      {
        PaintListView(folderCol[folderCol.Count - 2].ToString());
        folderCol.RemoveAt(folderCol.Count - 1);
      }
      else
        PaintListView(folderCol[0].ToString());
    }

    private void radioButtonLargeIcon_CheckedChanged(object sender, EventArgs e)
    {
      RadioButton rdb = (RadioButton)sender;
      if (rdb.Checked)
        this.listViewFilesAndFolders.View = View.LargeIcon;
    }

    private void radioButtonSmallIcon_CheckedChanged(object sender, EventArgs e)
    {
      RadioButton rdb = (RadioButton)sender;
      if (rdb.Checked)
        this.listViewFilesAndFolders.View = View.SmallIcon;
    }

    private void radioButtonList_CheckedChanged(object sender, EventArgs e)
    {
      RadioButton rdb = (RadioButton)sender;
      if (rdb.Checked)
        this.listViewFilesAndFolders.View = View.List;
    }

    private void radioButtonDetails_CheckedChanged(object sender, EventArgs e)
    {
      RadioButton rdb = (RadioButton)sender;
      if (rdb.Checked)
        this.listViewFilesAndFolders.View = View.Details;
    }

    private void radioButtonTile_CheckedChanged(object sender, EventArgs e)
    {
      RadioButton rdb = (RadioButton)sender;
      if (rdb.Checked)
        this.listViewFilesAndFolders.View = View.Tile;
    }
  }
}
