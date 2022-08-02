using System;
using Windows.Graphics.Printing;
using Windows.Graphics.Printing.OptionDetails;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Printing;

namespace FingerPaint
{
    public class BitmapPrintDocument : PrintDocument
    {
        Func<BitmapSource> getBitmap;
        IPrintDocumentSource printDocumentSource;

        // Element to print
        Border border = new Border
        {
            Child = new Image()
        };

        public BitmapPrintDocument(Func<BitmapSource> getBitmap)
        {
            this.getBitmap = getBitmap;

            // Get IPrintDocumentSource and attach event handlers
            printDocumentSource = this.DocumentSource;
            this.Paginate += OnPaginate;
            this.GetPreviewPage += OnGetPreviewPage;
            this.AddPages += OnAddPages;

            // Attach PrintManager handler
            PrintManager.GetForCurrentView().PrintTaskRequested += 
                                                OnPrintDocumentPrintTaskRequested;
        }

        async void OnPrintDocumentPrintTaskRequested(PrintManager sender, 
                                                     PrintTaskRequestedEventArgs args)
        {
            PrintTaskRequestedDeferral deferral = args.Request.GetDeferral();

            // Obtain PrintTask
            PrintTask printTask = args.Request.CreatePrintTask("Finger Paint", 
                                                               OnPrintTaskSourceRequested);

            // Probably set orientation to landscape
            PrintTaskOptionDetails optionDetails = 
                PrintTaskOptionDetails.GetFromPrintTaskOptions(printTask.Options);

            PrintOrientationOptionDetails orientation = 
                optionDetails.Options[StandardPrintTaskOptions.Orientation] as 
                                                            PrintOrientationOptionDetails;

            bool bitmapIsLandscape = false;

            await border.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    BitmapSource bitmapSource = getBitmap();
                    bitmapIsLandscape = bitmapSource.PixelWidth > bitmapSource.PixelHeight;
                });

            orientation.TrySetValue(bitmapIsLandscape ? PrintOrientation.Landscape : 
                                                        PrintOrientation.Portrait);

            deferral.Complete();
        }

        void OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs args)
        {
            args.SetSource(printDocumentSource);
        }

        void OnPaginate(object sender, PaginateEventArgs args)
        {
            PrintPageDescription pageDesc = args.PrintTaskOptions.GetPageDescription(0);

            // Get the Bitmap
            (border.Child as Image).Source = getBitmap();

            // Set Padding on the Border
            double left = pageDesc.ImageableRect.Left;
            double top = pageDesc.ImageableRect.Top;
            double right = pageDesc.PageSize.Width - left - pageDesc.ImageableRect.Width;
            double bottom = pageDesc.PageSize.Height - top - pageDesc.ImageableRect.Height;
            border.Padding = new Thickness(left, top, right, bottom);
            
            this.SetPreviewPageCount(1, PreviewPageCountType.Final);
        }

        void OnGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            this.SetPreviewPage(args.PageNumber, border);            
        }

        void OnAddPages(object sender, AddPagesEventArgs args)
        {
            this.AddPage(border);
            this.AddPagesComplete();
        }
    }
}
