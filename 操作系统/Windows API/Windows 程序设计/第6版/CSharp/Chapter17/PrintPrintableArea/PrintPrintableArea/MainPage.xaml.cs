using Windows.Graphics.Printing;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Printing;

namespace PrintPrintableArea
{
    public sealed partial class MainPage : Page
    {
        PrintDocument printDocument;
        IPrintDocumentSource printDocumentSource;

        // Element to print
        Border border = new Border
        {
            Background = new SolidColorBrush(Colors.Red),

            Child = new Border
            {
                Background = new SolidColorBrush(Colors.White),
                BorderBrush = new SolidColorBrush(Colors.Black),
                BorderThickness = new Thickness(1),
                Child = new TextBlock
                {
                    Text = "Print Printable Area",
                    FontFamily = new FontFamily("Times New Roman"),
                    FontSize = 24,
                    Foreground = new SolidColorBrush(Colors.Black),
                    HorizontalAlignment = HorizontalAlignment.Center,
                    VerticalAlignment = VerticalAlignment.Center
                }
            }
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
            PrintManager.GetForCurrentView().PrintTaskRequested += OnPrintManagerPrintTaskRequested;

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
            args.Request.CreatePrintTask("Print Printable Area", (requestArgs) =>
            {
                requestArgs.SetSource(printDocumentSource);
            });
        }

        void OnPrintDocumentPaginate(object sender, PaginateEventArgs args)
        {
            PrintPageDescription printPageDescription = args.PrintTaskOptions.GetPageDescription(0);

            // Set Padding on outer Border
            double left = printPageDescription.ImageableRect.Left;
            double top = printPageDescription.ImageableRect.Top;
            double right = printPageDescription.PageSize.Width 
                                    - left - printPageDescription.ImageableRect.Width;
            double bottom = printPageDescription.PageSize.Height 
                                    - top - printPageDescription.ImageableRect.Height;
            border.Padding = new Thickness(left, top, right, bottom);

            printDocument.SetPreviewPageCount(1, PreviewPageCountType.Final);
        }

        void OnPrintDocumentGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            printDocument.SetPreviewPage(args.PageNumber, border);
        }

        void OnPrintDocumentAddPages(object sender, AddPagesEventArgs args)
        {
            printDocument.AddPage(border);
            printDocument.AddPagesComplete();
        }
    }
}
