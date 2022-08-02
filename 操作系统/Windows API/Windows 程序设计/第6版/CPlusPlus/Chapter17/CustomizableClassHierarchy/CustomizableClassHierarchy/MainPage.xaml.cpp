//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace CustomizableClassHierarchy;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Printing;
using namespace Windows::Graphics::Printing::OptionDetails;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Printing;

using namespace ReflectionHelper;

MainPage::MainPage()
{
    InitializeComponent();

    rootTypeInfo = ref new TypeInformation(DependencyObject::typeid);
    classes = ref new Vector<TypeInformation^>();
    highlightBrush = ref new SolidColorBrush((ref new UISettings())->UIElementColor(UIElementType::Highlight));

    // Accumulate all the classes that derive from DependencyObject
    AddToClassList(DependencyObject::typeid);

    // Sort them alphabetically by name
    std::sort(begin(classes), end(classes), [](TypeInformation^ ti1, TypeInformation^ ti2)
    {
        return wcscmp(ti1->Name->Data(), ti2->Name->Data()) == -1;
    });

    // Put all these sorted classes into a tree structure
    ClassAndSubclasses^ rootClass = ref new ClassAndSubclasses(rootTypeInfo);
    AddToTree(rootClass, classes);

    // New stuff for printing
    printerTextBlocks = ref new Vector<TextBlock^>();
    blackBrush = ref new SolidColorBrush(Colors::Black);
    printerPages = ref new Vector<UIElement^>();

    // Display the tree using TextBlock's added to StackPanel
    DisplayAndPrinterPrep(rootClass, 0);

    // Create PrintDocument and attach handlers
    printDocument = ref new PrintDocument();
    printDocumentSource = printDocument->DocumentSource;
    printDocument->Paginate += ref new PaginateEventHandler(this, &MainPage::OnPrintDocumentPaginate);
    printDocument->GetPreviewPage += ref new GetPreviewPageEventHandler(this, &MainPage::OnPrintDocumentGetPreviewPage);
    printDocument->AddPages += ref new AddPagesEventHandler(this, &MainPage::OnPrintDocumentAddPages);

    // Initial values of custom printer settings
    fontSize = (ref new TextBlock())->FontSize;
    leftMargin = 96;     // 1 inch
    topMargin = 72;      // 3/4 inch
    rightMargin = 96;
    bottomMargin = 72;
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    // Attach PrintManager handler
    PrintManager^ printManager = PrintManager::GetForCurrentView();
    printTaskRequestedEventToken = printManager->PrintTaskRequested += ref new TypedEventHandler<PrintManager^, PrintTaskRequestedEventArgs^>(this, &MainPage::OnPrintManagerPrintTaskRequested);
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    // Detach PrintManager handler
    PrintManager::GetForCurrentView()->PrintTaskRequested -= printTaskRequestedEventToken;
}

void MainPage::AddToClassList(Type^ sampleType)
{
    AssemblyInformation^ assemblyInfo = ref new AssemblyInformation(sampleType);

    for each (TypeInformation^ typeInfo in assemblyInfo->ExportedTypes)
    {
        if (typeInfo->IsPublic && rootTypeInfo->IsAssignableFrom(typeInfo))
            classes->Append(typeInfo);
    }
}

void MainPage::AddToTree(ClassAndSubclasses^ node, IVector<TypeInformation^>^ classes)
{
    for each (TypeInformation^ typeInfo in classes)
    {
        TypeInformation^ baseTypeInfo = typeInfo->BaseType;

        if (baseTypeInfo->Equals(node->Parent))
        {
            ClassAndSubclasses^ subclass = ref new ClassAndSubclasses(typeInfo);
            node->Subclasses->Append(subclass);
            AddToTree(subclass, classes);
        }
    }
}

void MainPage::DisplayAndPrinterPrep(ClassAndSubclasses^ node, int indent)
{
    TypeInformation^ typeInfo = node->Parent;

    // Create TextBlock and add to StackPanel
    TextBlock^ txtblk = CreateTextBlock(typeInfo, indent);
    stackPanel->Children->Append(txtblk);

    // Create TextBlock and add to printer list
    txtblk = CreateTextBlock(typeInfo, indent);
    txtblk->Foreground = blackBrush;
    printerTextBlocks->Append(txtblk);

    // Call this method recursively for all subclasses
    for each (ClassAndSubclasses^ subclass in node->Subclasses)
        DisplayAndPrinterPrep(subclass, indent + 1);
}

TextBlock^ MainPage::CreateTextBlock(TypeInformation^ typeInfo, int indent)
{
    // Create TextBlock 
    TextBlock^ txtblk = ref new TextBlock();

    // Indent spaces
    for (int i = 0; i < indent ; i++)
    {
        Run^ run = ref new Run();
        run->Text = "        ";
        txtblk->Inlines->Append(run);
    }

    // Class name
    Run^ run = ref new Run();
    run->Text = typeInfo->Name;
    txtblk->Inlines->Append(run);

    // Indicate if the class is sealed
    if (typeInfo->IsSealed)
    {
        run = ref new Run();
        run->Text = " (sealed)";
        run->Foreground = highlightBrush;
        txtblk->Inlines->Append(run);
    }

    // Indicate if the class can't be instantiated
    IIterable<ConstructorInformation^>^ constructorInfos = typeInfo->DeclaredConstructors;
    int publicConstructorCount = 0;

    for each (ConstructorInformation^ constructorInfo in constructorInfos) 
    {
        if (constructorInfo->IsPublic)
            publicConstructorCount += 1;
    }

    if (publicConstructorCount == 0)
    {
        run = ref new Run();
        run->Text = " (non-instantiable)";
        run->Foreground = highlightBrush;
        txtblk->Inlines->Append(run);
    }
    return txtblk;
}

void MainPage::OnPrintManagerPrintTaskRequested(PrintManager^ sender, PrintTaskRequestedEventArgs^ args)
{
    PrintTask^ printTask = args->Request->CreatePrintTask("Print Printable Area", 
                                                          ref new PrintTaskSourceRequestedHandler(
        [this](PrintTaskSourceRequestedArgs^ args)
        {
            args->SetSource(printDocumentSource);
        }));

    PrintTaskOptionDetails^ optionDetails = 
                    PrintTaskOptionDetails::GetFromPrintTaskOptions(printTask->Options);

    // Add item for font size
    optionDetails->CreateTextOption("idFontSize", "Font size (in points)");
    optionDetails->DisplayedOptions->Append("idFontSize");
    optionDetails->Options->Lookup("idFontSize")->TrySetValue((72 * fontSize / 96).ToString());

    // Add items for page margins
    optionDetails->CreateTextOption("idLeftMargin", "Left margin (in inches)");
    optionDetails->DisplayedOptions->Append("idLeftMargin");
    optionDetails->Options->Lookup("idLeftMargin")->TrySetValue((leftMargin / 96).ToString());

    optionDetails->CreateTextOption("idTopMargin", "Top margin (in inches)");
    optionDetails->DisplayedOptions->Append("idTopMargin");
    optionDetails->Options->Lookup("idTopMargin")->TrySetValue((topMargin / 96).ToString());

    optionDetails->CreateTextOption("idRightMargin", "Right margin (in inches)");
    optionDetails->DisplayedOptions->Append("idRightMargin");
    optionDetails->Options->Lookup("idRightMargin")->TrySetValue((rightMargin / 96).ToString());

    optionDetails->CreateTextOption("idBottomMargin", "Bottom margin (in inches)");
    optionDetails->DisplayedOptions->Append("idBottomMargin");
    optionDetails->Options->Lookup("idBottomMargin")->TrySetValue((bottomMargin / 96).ToString());

    // Set handler for the option changing
    optionDetails->OptionChanged += ref new TypedEventHandler<PrintTaskOptionDetails^, PrintTaskOptionChangedEventArgs^>(this, &MainPage::OnOptionDetailsOptionsChanged);
}

void MainPage::OnOptionDetailsOptionsChanged(PrintTaskOptionDetails^ sender, PrintTaskOptionChangedEventArgs^ args)
{
    if (args->OptionId == nullptr)
        return;

    String^ optionId = dynamic_cast<String^>(args->OptionId);
    String^ strValue = sender->Options->Lookup(optionId)->Value->ToString();
    String^ errorText = "";
    float value = 0;
    wchar_t overflow[10];

    if (optionId == "idFontSize")
    {
        if (1 != swscanf_s(strValue->Data(), L"%f %s", &value, overflow, 10))
            errorText = "Value must be numeric";

        else if (value < 4 || value > 36)
            errorText = "Value must be between 4 and 36";
    }
    else if (optionId == "idLeftMargin" || 
             optionId == "idTopMargin" || 
             optionId == "idRightMargin" || 
             optionId == "idBottomMargin")
    {
        if (1 != swscanf_s(strValue->Data(), L"%f %s", &value, overflow, 10))
            errorText = "Value must be numeric";

        else if (value < 0 || value > 2)
            errorText = "Value must be between 0 and 2";
    }
    
    sender->Options->Lookup(optionId)->ErrorText = errorText;

    // If there's no error, then invalidate the preview
    if (errorText == "")
    {
        this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler(
        [this]()
        {
            printDocument->InvalidatePreview();
        }));
    }
}

void MainPage::OnPrintDocumentPaginate(Object^ sender, PaginateEventArgs^ args)
{
    // Get values of custom settings
    PrintTaskOptionDetails^ optionDetails = 
                    PrintTaskOptionDetails::GetFromPrintTaskOptions(args->PrintTaskOptions);

    float value;
    swscanf_s(dynamic_cast<String^>(optionDetails->Options->Lookup("idFontSize")->Value)->Data(), L"%f", &value);
    fontSize = 96 * value / 72;

    swscanf_s(dynamic_cast<String^>(optionDetails->Options->Lookup("idLeftMargin")->Value)->Data(), L"%f", &value);
    leftMargin = 96 * value;

    swscanf_s(dynamic_cast<String^>(optionDetails->Options->Lookup("idTopMargin")->Value)->Data(), L"%f", &value);
    topMargin = 96 * value;

    swscanf_s(dynamic_cast<String^>(optionDetails->Options->Lookup("idRightMargin")->Value)->Data(), L"%f", &value);
    rightMargin = 96 * value;

    swscanf_s(dynamic_cast<String^>(optionDetails->Options->Lookup("idBottomMargin")->Value)->Data(), L"%f", &value);
    bottomMargin = 96 * value;

    // Set FontSize of stored TextBlock's
    for each(TextBlock^ txtblk in printerTextBlocks)
    {
        txtblk->FontSize = fontSize;
    }

    // Clear out previous printerPage collection
    for each(UIElement^ printerPage in printerPages) 
    {
        dynamic_cast<Panel^>(dynamic_cast<Border^>(printerPage)->Child)->Children->Clear();
    }

    printerPages->Clear();

    // Initialize page construction
    Border^ border = nullptr;
    StackPanel^ stackPanel = nullptr;
    double maxPageHeight = 0;
    double pageHeight = 0;

    // Look through the list of TextBlock's
    for (unsigned int index = 0; index < printerTextBlocks->Size; index++)
    {
        // A null Border object signals a new page
        if (border == nullptr)
        {
            // Calculate the height available for text
            unsigned int pageNumber = (unsigned int)printerPages->Size;
            maxPageHeight = 
                args->PrintTaskOptions->GetPageDescription(pageNumber).PageSize.Height;
            maxPageHeight -= topMargin + bottomMargin;
            pageHeight = 0;

            // Create StackPanel and Border
            stackPanel = ref new StackPanel();
            border = ref new Border();
            border->Padding = ThicknessHelper::FromLengths(leftMargin, topMargin, rightMargin, bottomMargin);
            border->Child = stackPanel;

            // Add to the list of pages
            printerPages->Append(border);
        }

        // Get the TextBlock and measure it
        TextBlock^ txtblk = printerTextBlocks->GetAt(index);
        txtblk->Measure(Size::Empty);

        // Check if OK to add TextBlock to this page
        if (stackPanel->Children->Size == 0 ||
            pageHeight + txtblk->ActualHeight < maxPageHeight)
        {
            stackPanel->Children->Append(txtblk);
            pageHeight += ceil(txtblk->ActualHeight);
        }
        // Otherwise, it's the end of the page
        else
        {
            // No longer working with this border object
            border = nullptr;

            // Reprocess this TextBlock
            index--;
        }
    }

    // Notify about the final page count
    printDocument->SetPreviewPageCount(printerPages->Size, PreviewPageCountType::Final);
}

void MainPage::OnPrintDocumentGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    printDocument->SetPreviewPage(args->PageNumber, printerPages->GetAt(args->PageNumber - 1));
}

void MainPage::OnPrintDocumentAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    for each (UIElement^ printerPage in printerPages)
    {
        printDocument->AddPage(printerPage);
    }

    printDocument->AddPagesComplete();
}
