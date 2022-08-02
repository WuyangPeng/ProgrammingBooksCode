using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

using DirectXWrapper;

namespace LookAtFontMetrics
{
    public sealed partial class MainPage : Page
    {
        WriteFactory writeFactory;
        WriteFontCollection writeFontCollection;

        public MainPage()
        {
            this.InitializeComponent();

            writeFactory = new WriteFactory();
            writeFontCollection = writeFactory.GetSystemFontCollection();
            int count = writeFontCollection.GetFontFamilyCount();
            string[] fonts = new string[count];

            for (int i = 0; i < count; i++)
            {
                WriteFontFamily writeFontFamily = writeFontCollection.GetFontFamily(i);

                WriteLocalizedStrings writeLocalizedStrings = writeFontFamily.GetFamilyNames();

                int nameCount = writeLocalizedStrings.GetCount();
                int index;

                if (writeLocalizedStrings.FindLocaleName("en-us", out index))
                {
                    fonts[i] = writeLocalizedStrings.GetString(index);
                }
            }

            lstbox.ItemsSource = fonts;

            Loaded += (sender, args) =>
                {
                    lstbox.SelectedIndex = 0;
                };
        }

        void OnListBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            string fontFamily = (sender as ListBox).SelectedItem as string;

            if (fontFamily == null)
                return;

            txtblk.FontFamily = new FontFamily(fontFamily);

            int index;
            if (writeFontCollection.FindFamilyName(fontFamily, out index))
            {
                WriteFontFamily writeFontFamily = writeFontCollection.GetFontFamily(index);
                WriteFont writeFont = writeFontFamily.GetFirstMatchingFont(FontWeights.Normal,
                                                                           FontStretch.Normal,
                                                                           FontStyle.Normal);
                WriteFontMetrics fontMetrics = writeFont.GetMetrics();
                double fontSize = txtblk.FontSize;
                double ascent = fontSize * fontMetrics.Ascent / fontMetrics.DesignUnitsPerEm;
                double capsHeight = fontSize * fontMetrics.CapHeight / fontMetrics.DesignUnitsPerEm;
                double xHeight = fontSize * fontMetrics.XHeight / fontMetrics.DesignUnitsPerEm;
                double descent = fontSize * fontMetrics.Descent / fontMetrics.DesignUnitsPerEm;
                double lineGap = fontSize * fontMetrics.LineGap / fontMetrics.DesignUnitsPerEm;

                baselineLine.Y1 = baselineLine.Y2 = ascent;
                capsHeightLine.Y1 = capsHeightLine.Y2 = ascent - capsHeight;
                xHeightLine.Y1 = xHeightLine.Y2 = ascent - xHeight;
                descenderLine.Y1 = descenderLine.Y2 = ascent + descent;
                lineGapLine.Y1 = lineGapLine.Y2 = ascent + descent + lineGap;
            }
        }

        void OnTextBlockSizeChanged(object sender, SizeChangedEventArgs args)
        {
            double width = txtblk.ActualWidth;
            ascenderLine.X2 = width;
            capsHeightLine.X2 = width;
            xHeightLine.X2 = width;
            baselineLine.X2 = width;
            descenderLine.X2 = width;
            lineGapLine.X2 = width;
        }
    }
}
