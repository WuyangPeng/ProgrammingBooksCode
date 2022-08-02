//---------------------------------------------------------------------
// ImageFilterTest.cs (c) 2007 by Charles Petzold for "Beautiful Code"
//---------------------------------------------------------------------
using System;
using System.Drawing;
using System.Windows.Forms;

class ImageFilterTest : ImageClip
{
    MenuItem miScale;
    MenuItem miGenerate;

    [STAThread]
    public new static void Main()
    {
        Application.Run(new ImageFilterTest());
    }

    public ImageFilterTest()
    {
        Text = strProgName = "Image Filter Test";

        // View menu
        MenuItem miView = new MenuItem("&View");
        Menu.MenuItems.Add(miView);

        // Scale menu item
        miScale = new MenuItem("&Scale Isotropically to Window");
        miScale.Click += new EventHandler(MenuViewIsotropicallyOnClick);
        miScale.Checked = true;
        miView.MenuItems.Add(miScale);

        // Filter menu
        MenuItem miFilter = new MenuItem("F&ilter");
        Menu.MenuItems.Add(miFilter);

        // Generate-Code menu item
        miGenerate = new MenuItem("&Use method that generate Intermediate Language");
        miGenerate.Click += new EventHandler(MenuFilterGenerateOnClick);
        miFilter.MenuItems.Add(miGenerate);

        // Filter items
        MenuItem mi = new MenuItem("3 \x00D7 3 Blur Filter");
        mi.Click += new EventHandler(FilterOnClick);
        mi.Tag = new ImageFilter(3, new double[] {1, 1, 1, 1, 1, 1, 1, 1, 1});
        miFilter.MenuItems.Add(mi);

        mi = new MenuItem("5 \x00D7 5 Blur Filter");
        mi.Click += new EventHandler(FilterOnClick);
        mi.Tag = new ImageFilter(5, new double[] {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
                                                  1, 1, 1, 1, 1 });
        miFilter.MenuItems.Add(mi);

        mi = new MenuItem("3 \x00D7 3 Sharpness Filter (0 -1 0, -1 5 -1, 0 -1 0)");
        mi.Click += new EventHandler(FilterOnClick);
        mi.Tag = new ImageFilter(3, new double[] { 0, -1, 0, -1, 5, -1, 0, -1, 0 });
        miFilter.MenuItems.Add(mi);

        mi = new MenuItem("3 \x00D7 3 Sharpness Filter (-1 -1 -1, -1 9 -1, -1 -1 -1)");
        mi.Click += new EventHandler(FilterOnClick);
        mi.Tag = new ImageFilter(3, new double[] {-1, -1, -1, -1, 9, -1, -1, -1, -1});
        miFilter.MenuItems.Add(mi);

        mi = new MenuItem("3 \x00D7 3 Edge-Detection Filter (-1 -1 -1, -1 8 -1, -1 -1 -1)");
        mi.Click += new EventHandler(FilterOnClick);
        mi.Tag = new ImageFilter(3, new double[] { -1, -1, -1, -1, 8, -1, -1, -1, -1 });
        miFilter.MenuItems.Add(mi);
    }

    // OnPaint handler to display bitmap full size or window size
    protected override void OnPaint(PaintEventArgs args)
    {
        if (miScale.Checked)
            base.OnPaint(args);

        else if (image != null)
        {
            Graphics grfx = args.Graphics;
            grfx.DrawImage(image, 0, 0);
        }
    }

    // Two handlers for checkable menu items
    void MenuViewIsotropicallyOnClick(object sender, EventArgs args)
    {
        miScale.Checked = !miScale.Checked;
        Invalidate();
    }
    void MenuFilterGenerateOnClick(object sender, EventArgs args)
    {
        miGenerate.Checked = !miGenerate.Checked;
    }

    // Menu event handler to apply the filter
    void FilterOnClick(object sender, EventArgs args)
    {
        if (!(image is Bitmap))
        {
            MessageBox.Show("Must have color bitmap to apply filter!", strProgName);
            return;
        }

        MenuItem mi = sender as MenuItem;

        Bitmap bmp = image as Bitmap;
        ImageFilter filter = mi.Tag as ImageFilter;

        Cursor cursorSave = Cursor.Current;
        Cursor.Current = Cursors.WaitCursor;

        DateTime dt = DateTime.Now;
        bool isSuccess = filter.ApplyFilter(bmp, miGenerate.Checked);
        TimeSpan ts = DateTime.Now - dt;

        Cursor.Current = cursorSave;

        if (isSuccess)
        {
            Invalidate();
            MessageBox.Show("Elapsed time = " + ts.TotalMilliseconds + " milliseconds", strProgName);
        }
        else
        {
            MessageBox.Show("Bitmap must have 24 or 32 bits per pixel!", strProgName);
        }
    }
}
