using Windows.Graphics.Printing;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Printing;

namespace HelloPrinter
{
    public sealed partial class MainPage : Page
    {
        PrintDocument printDocument;
        IPrintDocumentSource printDocumentSource;

        // UIElement  to print
        TextBlock txtblk = new TextBlock
        {
            Text = "Hello, Printer!",
            FontFamily = new FontFamily("Times New Roman"),
            FontSize = 48,
            Foreground = new SolidColorBrush(Colors.Black)
        };

        public MainPage()
        {
            this.InitializeComponent();

            // Create PrintDocument and attach handlers
            printDocument = new PrintDocument();
            printDocumentSource = printDocument.DocumentSource;
            printDocument.Paginate += OnPrintDocumentPaginate;
            printDocument.GetPreviewPage += OnPrintDocumentGetPreviewPage;
            printDocument.AddPages += OnPrintDocumentAddPages;
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            // Attach PrintManager handler
            PrintManager printManager = PrintManager.GetForCurrentView();
            printManager.PrintTaskRequested += OnPrintManagerPrintTaskRequested;

            base.OnNavigatedTo(args);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            // Detach PrintManager handler
            PrintManager.GetForCurrentView().PrintTaskRequested -= OnPrintManagerPrintTaskRequested;

            base.OnNavigatedFrom(e);
        }

        void OnPrintManagerPrintTaskRequested(PrintManager sender, PrintTaskRequestedEventArgs args)
        {
            args.Request.CreatePrintTask("Hello Printer", OnPrintTaskSourceRequested);
        }

        void OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs args)
        {
            args.SetSource(printDocumentSource);
        }

        void OnPrintDocumentPaginate(object sender, PaginateEventArgs args)
        {
            printDocument.SetPreviewPageCount(1, PreviewPageCountType.Final);
        }

        void OnPrintDocumentGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            printDocument.SetPreviewPage(args.PageNumber, txtblk);
        }

        void OnPrintDocumentAddPages(object sender, AddPagesEventArgs args)
        {
            printDocument.AddPage(txtblk);
            printDocument.AddPagesComplete();
        }
    }
}
