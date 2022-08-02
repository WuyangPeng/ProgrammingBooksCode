//----------------------------------------
// ImageClip.cs © 2001 by Charles Petzold
//----------------------------------------
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

class ImageClip: ImagePrint
{
     MenuItem miCut, miCopy, miPaste, miDel;

     [STAThread]
     public new static void Main()
     {
          Application.Run(new ImageClip());
     }
     public ImageClip()
     {
          Text = strProgName = "Image Clip";

               // Edit menu

          MenuItem mi = new MenuItem("&Edit");
          mi.Popup += new EventHandler(MenuEditOnPopup);
          Menu.MenuItems.Add(mi);
          int index = Menu.MenuItems.Count - 1;

               // Edit Cut menu item

          miCut = new MenuItem("Cu&t");
          miCut.Click += new EventHandler(MenuEditCutOnClick);
          miCut.Shortcut = Shortcut.CtrlX;
          Menu.MenuItems[index].MenuItems.Add(miCut);

               // Edit Copy menu item

          miCopy = new MenuItem("&Copy");
          miCopy.Click += new EventHandler(MenuEditCopyOnClick);
          miCopy.Shortcut = Shortcut.CtrlC;
          Menu.MenuItems[index].MenuItems.Add(miCopy);

               // Edit Paste menu item

          miPaste = new MenuItem("&Paste");
          miPaste.Click += new EventHandler(MenuEditPasteOnClick);
          miPaste.Shortcut = Shortcut.CtrlV;
          Menu.MenuItems[index].MenuItems.Add(miPaste);

               // Edit Delete menu item

          miDel = new MenuItem("De&lete");
          miDel.Click += new EventHandler(MenuEditDelOnClick);
          miDel.Shortcut = Shortcut.Del;
          Menu.MenuItems[index].MenuItems.Add(miDel);
     }
     void MenuEditOnPopup(object obj, EventArgs ea)
     {
          miCut.Enabled = 
          miCopy.Enabled = 
          miDel.Enabled = image != null;

          IDataObject data = Clipboard.GetDataObject();

          miPaste.Enabled = data.GetDataPresent(typeof(Bitmap)) ||
                            data.GetDataPresent(typeof(Metafile));
     }
     void MenuEditCutOnClick(object obj, EventArgs ea)
     {
          MenuEditCopyOnClick(obj, ea);
          MenuEditDelOnClick(obj, ea);
     }
     void MenuEditCopyOnClick(object obj, EventArgs ea)
     {
          Clipboard.SetDataObject(image, true);
     }
     void MenuEditPasteOnClick(object obj, EventArgs ea)
     {
          IDataObject data = Clipboard.GetDataObject();

          if (data.GetDataPresent(typeof(Metafile)))
               image = (Image) data.GetData(typeof(Metafile));

          else if (data.GetDataPresent(typeof(Bitmap)))
               image = (Image) data.GetData(typeof(Bitmap));

          strFileName = "Clipboard";
          Text = strProgName + " - " + strFileName;
          Invalidate();
     }
     void MenuEditDelOnClick(object obj, EventArgs ea)
     {
          image = null;
          strFileName = null;
          Text = strProgName;
          Invalidate();
     }
}
