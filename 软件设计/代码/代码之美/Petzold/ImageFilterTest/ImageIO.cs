//--------------------------------------
// ImageIO.cs © 2001 by Charles Petzold
//--------------------------------------
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

class ImageIO: ImageOpen
{
     MenuItem miSaveAs;

     public new static void Main()
     {
          Application.Run(new ImageIO());
     }
     public ImageIO()
     {
          Text = strProgName = "Image I/O";

          Menu.MenuItems[0].Popup += new EventHandler(MenuFileOnPopup);
          miSaveAs = new MenuItem("Save &As...");
          miSaveAs.Click += new EventHandler(MenuFileSaveAsOnClick);
          Menu.MenuItems[0].MenuItems.Add(miSaveAs);
     }
     void MenuFileOnPopup(object obj, EventArgs ea)
     {
          miSaveAs.Enabled = (image != null);
     }
     void MenuFileSaveAsOnClick(object obj, EventArgs ea)
     {
          SaveFileDialog savedlg = new SaveFileDialog();

          savedlg.InitialDirectory = Path.GetDirectoryName(strFileName);
          savedlg.FileName = Path.GetFileNameWithoutExtension(strFileName);
          savedlg.AddExtension = true;
          savedlg.Filter = "Windows Bitmap (*.bmp)|*.bmp|" +
                           "Graphics Interchange Format (*.gif)|*.gif|" +
                           "JPEG File Interchange Format (*.jpg)|" +
                              "*.jpg;*.jpeg;*.jfif|" +
                           "Portable Network Graphics (*.png)|*.png|" +
                           "Tagged Imaged File Format (*.tif)|*.tif;*.tiff";

          if (savedlg.ShowDialog() == DialogResult.OK)
          {
               try
               {
                    image.Save(savedlg.FileName);
               }
               catch (Exception exc)
               {
                    MessageBox.Show(exc.Message, Text);
                    return;
               }
               strFileName = savedlg.FileName;
               Text = strProgName + " - " + Path.GetFileName(strFileName);
          }
     }
}
                                   
