using System;
using System.Collections.Generic;
using Windows.Globalization;
using Windows.Graphics.Printing;
using Windows.Graphics.Printing.OptionDetails;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Printing;

namespace PrintMonthlyPlanner
{
    public sealed partial class MainPage : Page
    {
        PrintDocument printDocument;
        IPrintDocumentSource printDocumentSource;
        List<UIElement> calendarPages = new List<UIElement>();
        bool printingEnabled;

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

        void OnMonthYearChanged(object sender, EventArgs args)
        {
            // Calculate number of months and check it it's non-negative
            int printableMonths = GetPrintableMonthCount();
            printButton.Content = String.Format("Print {0} Month{1}", printableMonths,
                                                printableMonths > 1 ? "s" : "");
            printButton.IsEnabled = printableMonths > 0;
            
            // Attach or detach PrintManager handler
            if (printingEnabled != printableMonths > 0)
            {
                PrintManager printManager = PrintManager.GetForCurrentView();

                if (printableMonths > 0)
                    printManager.PrintTaskRequested += OnPrintManagerPrintTaskRequested;
                else
                    printManager.PrintTaskRequested -= OnPrintManagerPrintTaskRequested;

                printingEnabled = printableMonths > 0;
            }
        }

        int GetPrintableMonthCount()
        {
            Calendar cal1 = monthYearSelect1.MonthYear;
            Calendar cal2 = monthYearSelect2.MonthYear;
            return cal2.Month - cal1.Month + 1 + 12 * (cal2.Year - cal1.Year);
        }

        async void OnPrintButtonClick(object sender, RoutedEventArgs args)
        {
            await PrintManager.ShowPrintUIAsync();
        }

        void OnPrintManagerPrintTaskRequested(PrintManager sender, PrintTaskRequestedEventArgs args)
        {
            // Create PrintTask
            PrintTask printTask = args.Request.CreatePrintTask("Monthly Planner", 
                                                               OnPrintTaskSourceRequested);

            // Set orientation to landscape
            PrintTaskOptionDetails optionDetails = 
                PrintTaskOptionDetails.GetFromPrintTaskOptions(printTask.Options);

            PrintOrientationOptionDetails orientation =
                optionDetails.Options[StandardPrintTaskOptions.Orientation] as 
                                                                    PrintOrientationOptionDetails;

            orientation.TrySetValue(PrintOrientation.Landscape);
        }

        void OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs args)
        {
            args.SetSource(printDocumentSource);
        }

        void OnPrintDocumentPaginate(object sender, PaginateEventArgs args)
        {
            // Prepare to generate pages
            uint pageNumber = 0;
            calendarPages.Clear();
            Calendar calendar = monthYearSelect1.MonthYear.Clone();
            calendar.Day = 1;
            Brush black = new SolidColorBrush(Colors.Black);

            // For each month
            do
            {
                PrintPageDescription printPageDescription = 
                                        args.PrintTaskOptions.GetPageDescription(pageNumber);

                // Set Padding on outer Border
                double left = printPageDescription.ImageableRect.Left;
                double top = printPageDescription.ImageableRect.Top;
                double right = printPageDescription.PageSize.Width
                                        - left - printPageDescription.ImageableRect.Width;
                double bottom = printPageDescription.PageSize.Height
                                        - top - printPageDescription.ImageableRect.Height;
                Border border = new Border { Padding = new Thickness(left, top, right, bottom) };

                // Use Grid for calendar cells
                Grid grid = new Grid();
                border.Child = grid;
                int numberOfWeeks = (6 + (int)calendar.DayOfWeek + calendar.LastDayInThisMonth) / 7;

                for (int row = 0; row < numberOfWeeks + 1; row++)
                    grid.RowDefinitions.Add(new RowDefinition 
                    { 
                        Height = new GridLength(1, GridUnitType.Star) 
                    });

                for (int col = 0; col < 7; col++)
                    grid.ColumnDefinitions.Add(new ColumnDefinition 
                    { 
                        Width = new GridLength(1, GridUnitType.Star) 
                    });

                // Month and year display at top
                Viewbox viewbox = new Viewbox
                {
                    Child = new TextBlock
                    {
                        Text = calendar.MonthAsSoloString() + " " + calendar.YearAsString(),
                        Foreground = black,
                        FontSize = 96,
                        HorizontalAlignment = HorizontalAlignment.Center
                    }
                };
                Grid.SetRow(viewbox, 0);
                Grid.SetColumn(viewbox, 0);
                Grid.SetColumnSpan(viewbox, 7);
                grid.Children.Add(viewbox);

                // Now loop through the days of the month
                for (int day = 1, row = 1, col = (int)calendar.DayOfWeek;
                     day <= calendar.LastDayInThisMonth; day++)
                {
                    Border dayBorder = new Border
                    {
                        BorderBrush = black,

                        // Avoid double line drawing
                        BorderThickness = new Thickness
                        {
                            Left = day == 1 || col == 0 ? 1 : 0,
                            Top = day - 7 < 1 ? 1 : 0,
                            Right = 1,
                            Bottom = 1
                        },

                        // Put day of month in upper-left corner
                        Child = new TextBlock
                        {
                            Text = day.ToString(),
                            Foreground = black,
                            FontSize = 24,
                            HorizontalAlignment = HorizontalAlignment.Left,
                            VerticalAlignment = VerticalAlignment.Top
                        }
                    };
                    Grid.SetRow(dayBorder, row);
                    Grid.SetColumn(dayBorder, col);
                    grid.Children.Add(dayBorder);
                    
                    if (0 == (col = (col + 1) % 7))
                        row += 1;
                }
                calendarPages.Add(border);
                calendar.AddMonths(1);
                pageNumber += 1;
            }
            while (calendar.Year < monthYearSelect2.MonthYear.Year ||
                   calendar.Month <= monthYearSelect2.MonthYear.Month);

            printDocument.SetPreviewPageCount(calendarPages.Count, PreviewPageCountType.Final);
        }

        void OnPrintDocumentGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            printDocument.SetPreviewPage(args.PageNumber, calendarPages[args.PageNumber - 1]);
        }

        void OnPrintDocumentAddPages(object sender, AddPagesEventArgs args)
        {
            foreach (UIElement calendarPage in calendarPages)
                printDocument.AddPage(calendarPage);

            printDocument.AddPagesComplete();
        }
    }
}
