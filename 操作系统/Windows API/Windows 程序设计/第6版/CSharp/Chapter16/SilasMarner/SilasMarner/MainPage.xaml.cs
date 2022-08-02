using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Documents;
using Windows.UI.Xaml.Media;

namespace SilasMarner
{
    public sealed partial class MainPage : Page
    {
        double fractionRead;

        public MainPage()
        {
            this.InitializeComponent();

            // Save and reload fraction read
            IPropertySet propertySet = ApplicationData.Current.LocalSettings.Values;

            Application.Current.Suspending += (sender, args) =>
                {
                    propertySet["FractionRead"] = fractionRead;
                };

            if (propertySet.ContainsKey("FractionRead"))
                fractionRead = (double)propertySet["FractionRead"];
        }

        async void OnFlipViewSizeChanged(object sender, SizeChangedEventArgs args)
        {
            // Get the size of the FlipView
            Size containerSize = args.NewSize;

            // Actual value gets modified during processing here, so save it
            double saveFractionRead = fractionRead;

            // First time through after program is launched
            if (flipView.Items.Count == 0)
            {
                // Load book resource
                IList<string> bookLines = 
                    await PathIO.ReadLinesAsync("ms-appx:///Books/pg550.txt",
                                                UnicodeEncoding.Utf8);

                // Create RichTextBlock
                RichTextBlock richTextBlock = new RichTextBlock
                {
                    FontSize = 22,
                    Foreground = new SolidColorBrush(Colors.Black)
                };

                // Create paragraphs
                Paragraph paragraph = new Paragraph();
                paragraph.Margin = new Thickness(12);
                richTextBlock.Blocks.Add(paragraph);

                foreach (string line in bookLines)
                {
                    // End of paragraph, make new Paragraph
                    if (line.Length == 0)
                    {
                        paragraph = new Paragraph();
                        paragraph.Margin = new Thickness(12);
                        richTextBlock.Blocks.Add(paragraph);
                    }
                    // Continue the paragraph
                    else
                    {
                        string textLine = line;
                        char lastChar = line[line.Length - 1];

                        if (lastChar != ' ')
                            textLine += ' ';

                        if (line[0] == ' ')
                            paragraph.Inlines.Add(new LineBreak());

                        paragraph.Inlines.Add(new Run { Text = textLine });
                    }
                }

                // Make RichTextBlock the same size as the FlipView
                flipView.Items.Add(richTextBlock);
                richTextBlock.Measure(containerSize);

                // Generate RichTextBlockOverflow elements
                if (richTextBlock.HasOverflowContent)
                {
                    // Add the first one
                    RichTextBlockOverflow richTextBlockOverflow = new RichTextBlockOverflow();
                    richTextBlock.OverflowContentTarget = richTextBlockOverflow;
                    flipView.Items.Add(richTextBlockOverflow);
                    richTextBlockOverflow.Measure(containerSize);

                    // Add subsequent ones
                    while (richTextBlockOverflow.HasOverflowContent)
                    {
                        RichTextBlockOverflow newRichTextBlockOverflow = new RichTextBlockOverflow();
                        richTextBlockOverflow.OverflowContentTarget = newRichTextBlockOverflow;
                        richTextBlockOverflow = newRichTextBlockOverflow;
                        flipView.Items.Add(richTextBlockOverflow);
                        richTextBlockOverflow.Measure(containerSize);
                    }
                }
            }
            // Subsequent SizeChanged events
            else
            {
                // Resize all the items in the FlipView
                foreach (object obj in flipView.Items)
                {
                    (obj as FrameworkElement).Measure(containerSize);
                }

                // Generate new RichTextBlockOverflow elements if needed
                while ((flipView.Items[flipView.Items.Count - 1] 
                                    as RichTextBlockOverflow).HasOverflowContent)
                {
                    RichTextBlockOverflow richTextBlockOverflow = 
                            flipView.Items[flipView.Items.Count - 1] as RichTextBlockOverflow;
                    RichTextBlockOverflow newRichTextBlockOverflow = new RichTextBlockOverflow();
                    richTextBlockOverflow.OverflowContentTarget = newRichTextBlockOverflow;
                    richTextBlockOverflow = newRichTextBlockOverflow;
                    flipView.Items.Add(richTextBlockOverflow);
                    richTextBlockOverflow.Measure(args.NewSize);
                }
                // Remove superfluous RichTextBlockOverflow elements
                while (!(flipView.Items[flipView.Items.Count - 2] 
                                    as RichTextBlockOverflow).HasOverflowContent)
                {
                    flipView.Items.RemoveAt(flipView.Items.Count - 1);
                }
            }
            
            // Initialize the header and Slider
            int count = flipView.Items.Count;
            pageNumber.Text = "1";              // probably modified soon
            pageCount.Text = count.ToString();
            pageSlider.Minimum = 1;
            pageSlider.Maximum = flipView.Items.Count;
            pageSlider.Value = 1;               // probably modified soon

            // Go to approximate page
            fractionRead = saveFractionRead;
            flipView.SelectedIndex = (int)Math.Min(count - 1, fractionRead * count);
        }

        void OnFlipViewSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            int pageNum = flipView.SelectedIndex + 1;
            pageNumber.Text = pageNum.ToString();
            fractionRead = (pageNum - 1.0) / flipView.Items.Count;
            pageSlider.Value = pageNum;
        }

        void OnPageSliderValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            flipView.SelectedIndex = Math.Min(flipView.Items.Count, (int)args.NewValue) - 1;
        }
    }
}
