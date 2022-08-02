//-----------------------------------------
// ImagePrint.cs © 2001 by Charles Petzold
//-----------------------------------------
using System;
using System.Drawing;
using System.Drawing.Printing;
using System.Windows.Forms;

class ImagePrint: ImageIO
{
     PrintDocument   prndoc = new PrintDocument();
     PageSetupDialog setdlg = new PageSetupDialog();
     PrintDialog     prndlg = new PrintDialog();

     MenuItem miFileSet, miFilePrint, miFileProps;

     public new static void Main()
     {
          Application.Run(new ImagePrint());
     }
     public ImagePrint()
     {
          Text = strProgName = "Image Print";

               // Initialize PrintDocument and common dialog boxes.

          prndoc.PrintPage += new PrintPageEventHandler(OnPrintPage);
          setdlg.Document = prndoc;
          prndlg.Document = prndoc;

               // Add menu items.

          Menu.MenuItems[0].Popup += new EventHandler(MenuFileOnPopup);
          Menu.MenuItems[0].MenuItems.Add("-");

               // File Page Setup item

          miFileSet = new MenuItem("Page Set&up...");
          miFileSet.Click += new EventHandler(MenuFileSetupOnClick);
          Menu.MenuItems[0].MenuItems.Add(miFileSet);

               // File Print item

          miFilePrint = new MenuItem("&Print...");
          miFilePrint.Click += new EventHandler(MenuFilePrintOnClick);
          miFilePrint.Shortcut = Shortcut.CtrlP;
          Menu.MenuItems[0].MenuItems.Add(miFilePrint);
          Menu.MenuItems[0].MenuItems.Add("-");

               // File Properties item

          miFileProps = new MenuItem("Propert&ies...");
          miFileProps.Click += new EventHandler(MenuFilePropsOnClick);
          Menu.MenuItems[0].MenuItems.Add(miFileProps);
     }
     protected override void OnPaint(PaintEventArgs pea)
     {
          if (image != null)
               ScaleImageIsotropically(pea.Graphics, image, ClientRectangle);
     }
     void MenuFileOnPopup(object obj, EventArgs ea)
     {
          miFileSet.Enabled = 
          miFilePrint.Enabled = 
          miFileProps.Enabled = (image != null);
     }
     void MenuFileSetupOnClick(object obj, EventArgs ea)
     {
          setdlg.ShowDialog();
     }
     void MenuFilePrintOnClick(object obj, EventArgs ea)
     {
          if (prndlg.ShowDialog() == DialogResult.OK)
          {
               prndoc.DocumentName = Text;
               prndoc.Print();
          }
     }
     void MenuFilePropsOnClick(object obj, EventArgs ea)
     {
          string str = 
               "Size = " + image.Size + 
               "\nHorizontal Resolution = " + image.HorizontalResolution +
               "\nVertical Resolution = " + image.VerticalResolution +
               "\nPhysical Dimension = " + image.PhysicalDimension +
               "\nPixel Format = " + image.PixelFormat;

          MessageBox.Show(str, "Image Properties");
     }
     void OnPrintPage(object obj, PrintPageEventArgs ppea)
     {
          Graphics   grfx  = ppea.Graphics;
          RectangleF rectf = new RectangleF(
               ppea.MarginBounds.Left - 
               (ppea.PageBounds.Width - grfx.VisibleClipBounds.Width) / 2,
               ppea.MarginBounds.Top - 
               (ppea.PageBounds.Height - grfx.VisibleClipBounds.Height) / 2,
               ppea.MarginBounds.Width,
               ppea.MarginBounds.Height);

          ScaleImageIsotropically(grfx, image, rectf);
     }
     void ScaleImageIsotropically(Graphics grfx, Image image, 
                                  RectangleF rectf)
     {
          SizeF sizef = new SizeF(image.Width / image.HorizontalResolution,
                                  image.Height / image.VerticalResolution);

          float fScale = Math.Min(rectf.Width  / sizef.Width,
                                  rectf.Height / sizef.Height);

          sizef.Width  *= fScale;
          sizef.Height *= fScale;
          
          grfx.DrawImage(image, rectf.X + (rectf.Width  - sizef.Width ) / 2,
                                rectf.Y + (rectf.Height - sizef.Height) / 2,
                                sizef.Width, sizef.Height);
     }
}