//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "ClassAndSubclasses.h"

using namespace DependencyObjectClassHierarchy;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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

    // Display the tree using TextBlock's added to StackPanel
    Display(rootClass, 0);
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

void MainPage::Display(ClassAndSubclasses^ node, int indent)
{
    TypeInformation^ typeInfo = node->Parent;

    // Create TextBlock for node
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

    stackPanel->Children->Append(txtblk);

    for each (ClassAndSubclasses^ subclass in node->Subclasses)
        Display(subclass, indent + 1);
}
