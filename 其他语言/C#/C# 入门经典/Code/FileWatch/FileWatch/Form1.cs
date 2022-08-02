using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace FileWatch
{
    public partial class Form1 : Form
    {
        // File System Watcher object.
        private FileSystemWatcher watcher;
        private delegate void UpdateWatchTextDelegate(string newText);

        public Form1()
        {
            InitializeComponent();

            this.watcher = new FileSystemWatcher();
            this.watcher.Deleted +=
               new FileSystemEventHandler(this.OnDelete);
            this.watcher.Renamed +=
               new RenamedEventHandler(this.OnRenamed);
            this.watcher.Changed +=
               new FileSystemEventHandler(this.OnChanged);
            this.watcher.Created +=
               new FileSystemEventHandler(this.OnCreate);

            DirectoryInfo aDir = new DirectoryInfo(@"C:\FileLogs");
            if (!aDir.Exists)
                aDir.Create();
        }

              // Utility method to update watch text.
      public void UpdateWatchText(string newText)
      {
         lblWatch.Text = newText;
      }

      // Define the event handlers.
      public void OnChanged(object source, FileSystemEventArgs e)
      {
         try
         {
            StreamWriter sw =
               new StreamWriter("C:/FileLogs/Log.txt", true);
            sw.WriteLine("File: {0} {1}", e.FullPath,
                         e.ChangeType.ToString());
            sw.Close();
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Wrote change event to log");
         }
         catch (IOException)
         {
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Error Writing to log");
         }
      }

      public void OnRenamed(object source, RenamedEventArgs e)
      {
         try
         {
            StreamWriter sw =
               new StreamWriter("C:/FileLogs/Log.txt", true);
            sw.WriteLine("File renamed from {0} to {1}", e.OldName,
                         e.FullPath);
            sw.Close();
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Wrote renamed event to log");
         }
         catch (IOException)
         {
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Error Writing to log");
         }
      }

      public void OnDelete(object source, FileSystemEventArgs e)
      {
         try
         {
            StreamWriter sw =
               new StreamWriter("C:/FileLogs/Log.txt", true);
            sw.WriteLine("File: {0} Deleted", e.FullPath);
            sw.Close();
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Wrote delete event to log");
         }
         catch (IOException)
         {
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Error Writing to log");
         }
      }

      public void OnCreate(object source, FileSystemEventArgs e)
      {
         try
         {
            StreamWriter sw =
               new StreamWriter("C:/FileLogs/Log.txt", true);
            sw.WriteLine("File: {0} Created", e.FullPath);
            sw.Close();
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Wrote create event to log");
         }
         catch (IOException)
         {
            this.BeginInvoke(new UpdateWatchTextDelegate(UpdateWatchText),
               "Error Writing to log");
         }
      }

      private void cmdBrowse_Click(object sender, EventArgs e)
      {
          if (FileDialog.ShowDialog() != DialogResult.Cancel)
          {
              txtLocation.Text = FileDialog.FileName;
              cmdWatch.Enabled = true;
          }
      }

      private void cmdWatch_Click(object sender, EventArgs e)
      {
          watcher.Path = Path.GetDirectoryName(txtLocation.Text);
          watcher.Filter = Path.GetFileName(txtLocation.Text);
          watcher.NotifyFilter = NotifyFilters.LastWrite |
             NotifyFilters.FileName | NotifyFilters.Size;
          lblWatch.Text = "Watching " + txtLocation.Text;
          // Begin watching.
          watcher.EnableRaisingEvents = true;
      }
    }
}
