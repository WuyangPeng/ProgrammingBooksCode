//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PrintMonthlyPlanner;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::Graphics::Printing;
using namespace Windows::Graphics::Printing::OptionDetails;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Printing;

MainPage::MainPage()
{
    InitializeComponent();

    calendarPages = ref new Vector<UIElement^>();

    // Create PrintDocument and attach handlers
    printDocument = ref new PrintDocument();
    printDocumentSource = printDocument->DocumentSource;
    printDocument->Paginate += ref new PaginateEventHandler(this, &MainPage::OnPrintDocumentPaginate);
    printDocument->GetPreviewPage += ref new GetPreviewPageEventHandler(this, &MainPage::OnPrintDocumentGetPreviewPage);
    printDocument->AddPages += ref new AddPagesEventHandler(this, &MainPage::OnPrintDocumentAddPages);
}

void MainPage::OnMonthYearChanged(Object^ sender, Calendar^ args)
{
    // Calculate number of months and check if it's non-negative
    int printableMonths = GetPrintableMonthCount();
    printButton->Content = "Print " + printableMonths.ToString() + 
                           " Month" + (printableMonths > 1 ? "s" : "");
    printButton->IsEnabled = printableMonths > 0;

    // Attach or detach PrintManager handler
    if (printingEnabled != printableMonths > 0)
    {
        PrintManager^ printManager = PrintManager::GetForCurrentView();

        if (printableMonths > 0)
            printTaskRequestedEventToken = printManager->PrintTaskRequested += 
                    ref new TypedEventHandler<PrintManager^, PrintTaskRequestedEventArgs^>(this, &MainPage::OnPrintManagerPrintTaskRequested);
        else
            printManager->PrintTaskRequested -= printTaskRequestedEventToken;

        printingEnabled = printableMonths > 0;
    }
}

int MainPage::GetPrintableMonthCount()
{
    Calendar^ cal1 = this->monthYearSelect1->MonthYear;
    Calendar^ cal2 = this->monthYearSelect2->MonthYear;
    return cal2->Month - cal1->Month + 1 + 12 * (cal2->Year - cal1->Year);
}

void MainPage::OnPrintButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    PrintManager::ShowPrintUIAsync();
}

void MainPage::OnPrintManagerPrintTaskRequested(PrintManager^ sender, PrintTaskRequestedEventArgs^ args)
{
    // Create PrintTask
    PrintTask^ printTask = args->Request->CreatePrintTask("Monthly Planner", 
                ref new PrintTaskSourceRequestedHandler(this, &MainPage::OnPrintTaskSourceRequested));

    // Set orientation to landscape
    PrintTaskOptionDetails^ optionDetails = PrintTaskOptionDetails::GetFromPrintTaskOptions(printTask->Options);
    
    PrintOrientationOptionDetails^ orientation = dynamic_cast<PrintOrientationOptionDetails^>
        (optionDetails->Options->Lookup(StandardPrintTaskOptions::Orientation));

    orientation->TrySetValue(PrintOrientation::Landscape);
}

void MainPage::OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs^ args)
{
    args->SetSource(printDocumentSource);
}

void MainPage::OnPrintDocumentPaginate(Object^ sender, PaginateEventArgs^ args)
{
    // Prepare to generate pages
    int pageNumber = 0;
    calendarPages->Clear();
    Calendar^ calendar = monthYearSelect1->MonthYear->Clone();
    calendar->Day = 1;
    Brush^ black = ref new SolidColorBrush(Colors::Black);

    // For each month
    do
    {
        PrintPageDescription printPageDescripton = args->PrintTaskOptions->GetPageDescription(pageNumber);

        // Set Padding on outer Border
        double left = printPageDescripton.ImageableRect.Left;
        double top = printPageDescripton.ImageableRect.Top;
        double right = printPageDescripton.PageSize.Width - left - printPageDescripton.ImageableRect.Width;
        double bottom = printPageDescripton.PageSize.Height - top - printPageDescripton.ImageableRect.Height;
        Border^ border = ref new Border();
        border->Padding = ThicknessHelper::FromLengths(left, top, right, bottom);

        // Use Grid for calendar cells
        Grid^ grid = ref new Grid();
        border->Child = grid;
        int numberOfWeeks = (6 + (int)calendar->DayOfWeek + calendar->LastDayInThisMonth) / 7;

        for (int row = 0; row < numberOfWeeks + 1; row++)
        {
            RowDefinition^ rowdef = ref new RowDefinition();
            rowdef->Height = GridLengthHelper::FromValueAndType(1, GridUnitType::Star);
            grid->RowDefinitions->Append(rowdef);
        }
        
        for (int col = 0; col < 7; col++)
        {
            ColumnDefinition^ coldef = ref new ColumnDefinition();
            coldef->Width = GridLengthHelper::FromValueAndType(1, GridUnitType::Star);
            grid->ColumnDefinitions->Append(coldef);
        }

        // Month and year display at top
        TextBlock^ txtblk = ref new TextBlock();
        txtblk->Text = calendar->MonthAsSoloString() + " " + calendar->YearAsString();
        txtblk->Foreground = black;
        txtblk->FontSize = 96;
        txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;

        Viewbox^ viewbox = ref new Viewbox();
        viewbox->Child = txtblk;

        Grid::SetRow(viewbox, 0);
        Grid::SetColumn(viewbox, 0);
        Grid::SetColumnSpan(viewbox, 7);
        grid->Children->Append(viewbox);

        // Now loop throught the days of the month
        for (int day = 1, row = 1, col = (int)calendar->DayOfWeek;
            day <= calendar->LastDayInThisMonth; 
            day++)
        {
            // Put day of month in upper-left corner
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = day.ToString();
            txtblk->Foreground = black;
            txtblk->FontSize = 24;
            txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
            txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;

            Border^ dayBorder = ref new Border();
            dayBorder->Child = txtblk;
            dayBorder->BorderBrush = black;
            
            // Avoid double line drawing
            dayBorder->BorderThickness = 
                ThicknessHelper::FromLengths(day == 1 || col == 0 ? 1 : 0,
                                             day - 7 < 1 ? 1 : 0,
                                             1, 1);

            Grid::SetRow(dayBorder, row);
            Grid::SetColumn(dayBorder, col);
            grid->Children->Append(dayBorder);

            if (0 == (col = (col + 1) % 7))
                row += 1;
        }
        calendarPages->Append(border);
        calendar->AddMonths(1);
        pageNumber++;
    }
    while (calendar->Year < monthYearSelect2->MonthYear->Year ||
           calendar->Month <= monthYearSelect2->MonthYear->Month);

    printDocument->SetPreviewPageCount(calendarPages->Size, PreviewPageCountType::Final);
}

void MainPage::OnPrintDocumentGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    printDocument->SetPreviewPage(args->PageNumber, calendarPages->GetAt(args->PageNumber - 1));
}

void MainPage::OnPrintDocumentAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    std::for_each(begin(calendarPages), end(calendarPages), [this](UIElement^ calendarPage)
    {
        printDocument->AddPage(calendarPage);
    });

    printDocument->AddPagesComplete();
}
