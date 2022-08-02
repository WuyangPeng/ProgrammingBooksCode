using System;
using Windows.Graphics.Printing;
using Windows.Graphics.Printing.OptionDetails;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Printing;

namespace PrintableTomKitten
{
    public sealed partial class MainPage : Page
    {
        PrintDocument printDocument;
        IPrintDocumentSource printDocumentSource;
        CustomPageRange customPageRange;
        UIElement[] bookPages = 
        { 
            new TomKitten03(), new TomKitten04(), new TomKitten05(), new TomKitten06(),
            new TomKitten07(), new TomKitten08(), new TomKitten09(), new TomKitten10(), 
            new TomKitten11(), new TomKitten12(), new TomKitten13(), new TomKitten14(), 
            new TomKitten15(), new TomKitten16(), new TomKitten17(), new TomKitten18(),
            new TomKitten19(), new TomKitten20(), new TomKitten21(), new TomKitten22(),
            new TomKitten23(), new TomKitten24(), new TomKitten25(), new TomKitten26(),
            new TomKitten27(), new TomKitten28(), new TomKitten29(), new TomKitten30(),
            new TomKitten31(), new TomKitten32(), new TomKitten33(), new TomKitten34(),
            new TomKitten35(), new TomKitten36(), new TomKitten37(), new TomKitten38(),
            new TomKitten39(), new TomKitten40(), new TomKitten41(), new TomKitten42(),
            new TomKitten43(), new TomKitten44(), new TomKitten45(), new TomKitten46(),
            new TomKitten47(), new TomKitten48(), new TomKitten49(), new TomKitten50(),
            new TomKitten51(), new TomKitten52(), new TomKitten53(), new TomKitten54(),
            new TomKitten55(), new TomKitten56(), new TomKitten57(), new TomKitten58(),
            new TomKitten59()
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
            PrintTask printTask = args.Request.CreatePrintTask("The Tale of Tom Kitten", 
                                                               OnPrintTaskSourceRequested);

            // Get PrintTaskOptionDetails for making changes to options
            PrintTaskOptionDetails optionDetails = 
                PrintTaskOptionDetails.GetFromPrintTaskOptions(printTask.Options);

            // Create the custom item
            PrintCustomItemListOptionDetails pageRange = 
                                optionDetails.CreateItemListOption("idPrintRange", "Print range");
            pageRange.AddItem("idPrintAll", "Print all pages");
            pageRange.AddItem("idPrintCustom", "Print custom range");

            // Add it to the options
            optionDetails.DisplayedOptions.Add("idPrintRange");

            // Create a page-range edit item also, but this only 
            //      comes into play when user selects "Print custom range"
            optionDetails.CreateTextOption("idCustomRangeEdit", "Custom Range");

            // Set a handler for the OptionChanged event
            optionDetails.OptionChanged += OnOptionDetailsOptionChanged;
        }

        void OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs args)
        {
            args.SetSource(printDocumentSource);
        }

        async void OnOptionDetailsOptionChanged(PrintTaskOptionDetails sender, 
                                                PrintTaskOptionChangedEventArgs args)
        {
            if (args.OptionId == null)
                return;

            string optionId = args.OptionId.ToString();
            string strValue = sender.Options[optionId].Value.ToString();
            string errorText = String.Empty;

            switch (optionId)
            {
                case "idPrintRange":
                    switch (strValue)
                    {
                        case "idPrintAll":
                            if (sender.DisplayedOptions.Contains("idCustomRangeEdit"))
                                sender.DisplayedOptions.Remove("idCustomRangeEdit");
                            break;

                        case "idPrintCustom":
                            sender.DisplayedOptions.Add("idCustomRangeEdit");
                            break;
                    }
                    break;

                case "idCustomRangeEdit":
                    // Check to see if CustomPageRange accepts this
                    if (!new CustomPageRange(strValue, bookPages.Length).IsValid)
                    {
                        errorText = "Use the form 2-4, 7, 9-11";
                    }
                    break;
            }

            sender.Options[optionId].ErrorText = errorText;

            // If no error, then invalidate the preview
            if (String.IsNullOrEmpty(errorText))
            {
                await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    printDocument.InvalidatePreview();
                });
            }
        }

        void OnPrintDocumentPaginate(object sender, PaginateEventArgs args)
        {
            // Obtain the print range option
            PrintTaskOptionDetails optionDetails = 
                        PrintTaskOptionDetails.GetFromPrintTaskOptions(args.PrintTaskOptions);

            string strValue = optionDetails.Options["idPrintRange"].Value as string;

            if (strValue == "idPrintCustom")
            {
                // Parse the print range for GetPreviewPage and AddPages
                string strPageRange = optionDetails.Options["idCustomRangeEdit"].Value as string;
                customPageRange = new CustomPageRange(strPageRange, bookPages.Length);
            }
            else
            {
                // Make sure field is null if printing all pages
                customPageRange = null;
            }

            int pageCount = bookPages.Length;

            if (customPageRange != null && customPageRange.IsValid)
                pageCount = customPageRange.PageMapping.Count;

            printDocument.SetPreviewPageCount(pageCount, PreviewPageCountType.Final);
        }

        void OnPrintDocumentGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            int oneBasedIndex = args.PageNumber;

            if (customPageRange != null && customPageRange.IsValid)
                oneBasedIndex = customPageRange.PageMapping[args.PageNumber - 1];

            printDocument.SetPreviewPage(args.PageNumber, bookPages[oneBasedIndex - 1]);
        }

        void OnPrintDocumentAddPages(object sender, AddPagesEventArgs args)
        {
            if (customPageRange != null && customPageRange.IsValid)
            {
                foreach (int oneBasedIndex in customPageRange.PageMapping)
                    printDocument.AddPage(bookPages[oneBasedIndex - 1]);
            }
            else
            {
                foreach (UIElement bookPage in bookPages)
                    printDocument.AddPage(bookPage);
            }

            printDocument.AddPagesComplete();
        }
    }
}
