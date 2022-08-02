//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AnimationEaseGrapher;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Navigation;

// C# assembly
using namespace ReflectionHelper;

MainPage::MainPage()
{
    InitializeComponent();
    this->Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    TypeInformation^ baseTypeInfo = ref new TypeInformation(EasingFunctionBase::typeid);
    AssemblyInformation^ assemblyInfo = ref new AssemblyInformation(EasingFunctionBase::typeid);

    // Enumerate through all Windows Runtime types
    for each (TypeInformation^ typeInfo in assemblyInfo->ExportedTypes)
    {
        // Create RadioButton for each easing function
        if (typeInfo->IsPublic &&
            baseTypeInfo->IsAssignableFrom(typeInfo) &&
            !baseTypeInfo->Equals(typeInfo))
        {
            RadioButton^ radioButton = ref new RadioButton();
            radioButton->Content = typeInfo->Name;
            radioButton->Tag = typeInfo;
            radioButton->Margin = ThicknessHelper::FromUniformLength(6);
            radioButton->Checked += ref new RoutedEventHandler(this, &MainPage::OnEasingFunctionRadioButtonChecked);
            easingFunctionStackPanel->Children->Append(radioButton);
        }

        // Check the first RadioButton in the StackPanel (the one labeled "None")
        dynamic_cast<RadioButton^>(easingFunctionStackPanel->Children->GetAt(0))->IsChecked = true;
    }
}

void MainPage::OnEasingFunctionRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);
    TypeInformation^ typeInfo = dynamic_cast<TypeInformation^>(radioButton->Tag);
    easingFunction = nullptr;
    propertiesStackPanel->Children->Clear();

    // typeInfo is only null for "None" buton
    if (typeInfo != nullptr)
    {
        // Find a parameterless constructor and instantiate the easing function
        for each (ConstructorInformation^ constructorInfo in typeInfo->DeclaredConstructors)
        {
            if (constructorInfo->IsPublic && constructorInfo->GetParameters()->Length == 0)
            {
                this->easingFunction = dynamic_cast<EasingFunctionBase^>(constructorInfo->Invoke(nullptr));
            }
        }

        // Enumerate the easing function properties
        for each (PropertyInformation^ property in typeInfo->DeclaredProperties)
        {
            // We can only deal with properties of type int and double
            if (property->PropertyType.Name == "Int32" ||
                property->PropertyType.Name == "Double")
            {
                // Create a TextBlock for the property name
                TextBlock^ txtblk = ref new TextBlock();
                txtblk->Text = property->Name + ":";
                this->propertiesStackPanel->Children->Append(txtblk);

                // Create a Slider for the property value
                Slider^ slider = ref new Slider();
                slider->Width = 144;
                slider->Minimum = 0;
                slider->Maximum = 10;
                slider->Tag = property;

                if (property->PropertyType.Name == "Int32")
                {
                    slider->StepFrequency = 1;
                    slider->Value = (int)property->GetValue(this->easingFunction);
                }
                else
                {
                    slider->StepFrequency = 0.1;
                    slider->Value = (double)property->GetValue(this->easingFunction);
                }
                // Define the Slider event handler right here
                slider->ValueChanged += ref new RangeBaseValueChangedEventHandler(
                    [this](Object^ sliderSender, RangeBaseValueChangedEventArgs^ sliderArgs)
                {
                    Slider^ sliderChanging = dynamic_cast<Slider^>(sliderSender);
                    PropertyInformation^ property = dynamic_cast<PropertyInformation^>(sliderChanging->Tag);

                    if (property->PropertyType.Name == "Int32")
                        property->SetValue(easingFunction, (int)sliderArgs->NewValue);
                    else
                        property->SetValue(easingFunction, (double)sliderArgs->NewValue);

                    DrawNewGraph();
                });
                propertiesStackPanel->Children->Append(slider);
            }
        }
    }

    // Initialize EasingMode radio button
    for each (UIElement^ child in easingModeStackPanel->Children)
    {
        RadioButton^ easingModeRadioButton = dynamic_cast<RadioButton^>(child);
        easingModeRadioButton->IsEnabled = this->easingFunction != nullptr;
        easingModeRadioButton->IsChecked = 
            this->easingFunction != nullptr  &&
            this->easingFunction->EasingMode == (EasingMode)(int)easingModeRadioButton->Tag;
    }
    DrawNewGraph();
}

void MainPage::OnEasingModeRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);
    easingFunction->EasingMode = (EasingMode)(int)radioButton->Tag;
    DrawNewGraph();
}

void MainPage::OnDemoButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    // Set the selected easing function and start the animation
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup("storyboard"));
    dynamic_cast<DoubleAnimation^>(storyboard->Children->GetAt(1))->EasingFunction = easingFunction;
    storyboard->Begin();
}

void MainPage::DrawNewGraph()
{
    polyline->Points->Clear();

    if (easingFunction == nullptr)
    {
        polyline->Points->Append(Point(0, 0));
        polyline->Points->Append(Point(1000, 500));
        return;
    }

    for (int t = 0; t <= 100; t += 1)
    {
        float x = 10.0f * t;
        float y = (float)(500 * easingFunction->Ease(t / 100.0));
        polyline->Points->Append(Point(x, y));
    }
}
