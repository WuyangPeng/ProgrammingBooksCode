using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using DirectXWrapper;

namespace BaselineTiltedShadow
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

            foregroundTextBlock.FontFamily = new FontFamily(fontFamily);
            shadowTextBlock.FontFamily = foregroundTextBlock.FontFamily;

            int index;
            if (writeFontCollection.FindFamilyName(fontFamily, out index))
            {
                WriteFontFamily writeFontFamily = writeFontCollection.GetFontFamily(index);
                WriteFont writeFont = writeFontFamily.GetFirstMatchingFont(FontWeights.Normal,
                                                                           FontStretch.Normal,
                                                                           FontStyle.Normal);
                WriteFontMetrics fontMetrics = writeFont.GetMetrics();
                
                double fractionAboveBaseline = (double)fontMetrics.Ascent / 
                            (fontMetrics.Ascent + fontMetrics.Descent + fontMetrics.LineGap);

                shadowTextBlock.RenderTransformOrigin = new Point(0, fractionAboveBaseline);
            }
        }
    }
}
