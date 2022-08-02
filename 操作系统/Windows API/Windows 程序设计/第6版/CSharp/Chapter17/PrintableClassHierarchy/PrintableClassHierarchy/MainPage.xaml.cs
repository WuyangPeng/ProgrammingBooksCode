﻿using System;
using System.Collections.Generic;
using System.Reflection;
using Windows.Foundation;
using Windows.Graphics.Printing;
using Windows.UI;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Documents;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Printing;

namespace PrintableClassHierarchy
{
    public sealed partial class MainPage : Page
    {
        Type rootType = typeof(DependencyObject);
        TypeInfo rootTypeInfo = typeof(DependencyObject).GetTypeInfo();
        List<Type> classes = new List<Type>();
        Brush highlightBrush;

        // Printing support
        List<TextBlock> printerTextBlocks = new List<TextBlock>();
        Brush blackBrush = new SolidColorBrush(Colors.Black);

        PrintDocument printDocument;
        IPrintDocumentSource printDocumentSource;
        List<UIElement> printerPages = new List<UIElement>();

        public MainPage()
        {
            this.InitializeComponent();
            highlightBrush =
                new SolidColorBrush(new UISettings().UIElementColor(UIElementType.Highlight));

            // Accumulate all the classes that derive from DependencyObject 
            AddToClassList(typeof(Windows.UI.Xaml.DependencyObject));

            // Sort them alphabetically by name
            classes.Sort((t1, t2) =>
            {
                return String.Compare(t1.GetTypeInfo().Name, t2.GetTypeInfo().Name);
            });

            // Put all these sorted classes into a tree structure
            ClassAndSubclasses rootClass = new ClassAndSubclasses(rootType);
            AddToTree(rootClass, classes);

            // Display the tree using TextBlock's added to StackPanel
            DisplayAndPrinterPrep(rootClass, 0);

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

        void AddToClassList(Type sampleType)
        {
            Assembly assembly = sampleType.GetTypeInfo().Assembly;

            foreach (Type type in assembly.ExportedTypes)
            {
                TypeInfo typeInfo = type.GetTypeInfo();

                if (typeInfo.IsPublic && rootTypeInfo.IsAssignableFrom(typeInfo))
                    classes.Add(type);
            }
        }

        void AddToTree(ClassAndSubclasses parentClass, List<Type> classes)
        {
            foreach (Type type in classes)
            {
                Type baseType = type.GetTypeInfo().BaseType;

                if (baseType == parentClass.Type)
                {
                    ClassAndSubclasses subClass = new ClassAndSubclasses(type);
                    parentClass.Subclasses.Add(subClass);
                    AddToTree(subClass, classes);
                }
            }
        }

        void DisplayAndPrinterPrep(ClassAndSubclasses parentClass, int indent)
        {
            TypeInfo typeInfo = parentClass.Type.GetTypeInfo();

            // Create TextBlock and add to StackPanel
            TextBlock txtblk = CreateTextBlock(typeInfo, indent);
            stackPanel.Children.Add(txtblk);

            // Create TextBlock and add to printer list
            txtblk = CreateTextBlock(typeInfo, indent);
            txtblk.Foreground = blackBrush;
            printerTextBlocks.Add(txtblk);

            // Call this method recursively for all subclasses
            foreach (ClassAndSubclasses subclass in parentClass.Subclasses)
                DisplayAndPrinterPrep(subclass, indent + 1);
        }

        TextBlock CreateTextBlock(TypeInfo typeInfo, int indent)
        {
            // Create TextBlock with type name
            TextBlock txtblk = new TextBlock();
            txtblk.Inlines.Add(new Run { Text = new string(' ', 8 * indent) });
            txtblk.Inlines.Add(new Run { Text = typeInfo.Name });

            // Indicate if the class is sealed
            if (typeInfo.IsSealed)
                txtblk.Inlines.Add(new Run
                {
                    Text = " (sealed)",
                    Foreground = highlightBrush
                });

            // Indicate if the class can't be instantiated
            IEnumerable<ConstructorInfo> constructorInfos = typeInfo.DeclaredConstructors;
            int publicConstructorCount = 0;

            foreach (ConstructorInfo constructorInfo in constructorInfos)
                if (constructorInfo.IsPublic)
                    publicConstructorCount += 1;

            if (publicConstructorCount == 0)
                txtblk.Inlines.Add(new Run
                {
                    Text = " (non-instantiable)",
                    Foreground = highlightBrush
                });

            return txtblk;
        }

        void OnPrintManagerPrintTaskRequested(PrintManager sender, PrintTaskRequestedEventArgs args)
        {
            args.Request.CreatePrintTask("Dependency Property Class Hierarchy", (requestArgs) =>
            {
                requestArgs.SetSource(printDocumentSource);
            });
        }

        void OnPrintDocumentPaginate(object sender, PaginateEventArgs args)
        {
            // Verbosely set some variables for the page margin
            double leftMargin = 96;
            double topMargin = 96;
            double rightMargin = 96;
            double bottomMargin = 96;

            // Clear out previous printerPage collection
            foreach (UIElement printerPage in printerPages)
                ((printerPage as Border).Child as Panel).Children.Clear();

            printerPages.Clear();

            // Initialize page construction
            Border border = null;
            StackPanel stackPanel = null;
            double maxPageHeight = 0;
            double pageHeight = 0;

            // Look through the list of TextBlock's
            for (int index = 0; index < printerTextBlocks.Count; index++)
            {
                // A null Border object signals a new page
                if (border == null)
                {
                    // Calculate the height available for text
                    uint pageNumber = (uint)printerPages.Count;
                    maxPageHeight = 
                        args.PrintTaskOptions.GetPageDescription(pageNumber).PageSize.Height;
                    maxPageHeight -= topMargin + bottomMargin;
                    pageHeight = 0;

                    // Create StackPanel and Border
                    stackPanel = new StackPanel();
                    border = new Border
                    {
                        Padding = new Thickness(leftMargin, topMargin, rightMargin, bottomMargin),
                        Child = stackPanel
                    };

                    // Add to the list of pages
                    printerPages.Add(border);
                }

                // Get the TextBlock and measure it
                TextBlock txtblk = printerTextBlocks[index];
                txtblk.Measure(Size.Empty);

                // Check if OK to add TextBlock to this page
                if (stackPanel.Children.Count == 0 ||
                    pageHeight + txtblk.ActualHeight < maxPageHeight)
                {
                    stackPanel.Children.Add(txtblk);
                    pageHeight += Math.Ceiling(txtblk.ActualHeight);
                }
                // Otherwise, it's the end of the page
                else
                {
                    // No longer working with this Border object
                    border = null;

                    // Reprocess this TextBlock
                    index--;
                }
            }

            // Notify about the final page count
            printDocument.SetPreviewPageCount(printerPages.Count, PreviewPageCountType.Final);
        }

        void OnPrintDocumentGetPreviewPage(object sender, GetPreviewPageEventArgs args)
        {
            printDocument.SetPreviewPage(args.PageNumber, printerPages[args.PageNumber - 1]);
        }

        void OnPrintDocumentAddPages(object sender, AddPagesEventArgs args)
        {
            foreach (UIElement printerPage in printerPages)
                printDocument.AddPage(printerPage);

            printDocument.AddPagesComplete();
        }
    }
}
