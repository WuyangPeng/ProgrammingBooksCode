using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace BerniceBobsHerHair
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnRichTextBlockSizeChanged(object sender, SizeChangedEventArgs args)
        {
            RichTextBlock richTextBlock = sender as RichTextBlock;
            
            if (richTextBlock.ActualHeight == 0)
                return;
            
            // Get rid of all previous RichTextBlockOverflow objects
            while (stackPanel.Children.Count > 1)
                stackPanel.Children.RemoveAt(1);

            if (!richTextBlock.HasOverflowContent)
                return;

            // Create first RichTextBlockOverflow
            RichTextBlockOverflow richTextBlockOverflow = new RichTextBlockOverflow();
            richTextBlock.OverflowContentTarget = richTextBlockOverflow;
            stackPanel.Children.Add(richTextBlockOverflow);

            // Measure it
            richTextBlockOverflow.Measure(new Size(richTextBlockOverflow.Width, this.ActualHeight));

            // If it has overflow content, repeat the process
            while (richTextBlockOverflow.HasOverflowContent)
            {
                RichTextBlockOverflow newRichTextBlockOverflow = new RichTextBlockOverflow();
                richTextBlockOverflow.OverflowContentTarget = newRichTextBlockOverflow;
                richTextBlockOverflow = newRichTextBlockOverflow;
                stackPanel.Children.Add(richTextBlockOverflow);
                richTextBlockOverflow.Measure(new Size(richTextBlockOverflow.Width, this.ActualHeight));
            }
        }
    }
}
