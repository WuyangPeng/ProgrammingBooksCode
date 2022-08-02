#pragma once

namespace SilentPiano
{
    // Compiler prohibits this attribute "repeated" but the program works regardless
    // [Windows::UI::Xaml::TemplateVisualState(Name = "Normal", GroupName = "CommonStates")]
    // [Windows::UI::Xaml::TemplateVisualState(Name = "Pressed", GroupName = "CommonStates")]
    public ref class Key sealed : public Windows::UI::Xaml::Controls::Control
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ isPressedProperty;
        Platform::Collections::Vector<unsigned int>^ pointerList;

    public:
        Key();

        static property Windows::UI::Xaml::DependencyProperty^ IsPressedProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        property bool IsPressed
        {
            void set(bool);
            bool get();
        };

       protected:
        virtual void OnPointerEntered(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e) override;
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e) override;
        virtual void OnPointerExited(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e) override;

    private:
        void AddToList(unsigned int id);
        void RemoveFromList(unsigned int id);
        void CheckList();
        static void OnIsPressedChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
    };
}
