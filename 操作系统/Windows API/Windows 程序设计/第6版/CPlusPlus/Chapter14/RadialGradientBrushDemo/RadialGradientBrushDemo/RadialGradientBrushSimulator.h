#pragma once

namespace RadialGradientBrushDemo
{
    public ref class RadialGradientBrushSimulator sealed : public Windows::UI::Xaml::Controls::Control // ::FrameworkElement
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ gradientOriginProperty;
        static Windows::UI::Xaml::DependencyProperty^ innerColorProperty;
        static Windows::UI::Xaml::DependencyProperty^ outerColorProperty;
        static Windows::UI::Xaml::DependencyProperty^ clipToEllipseProperty;
        static Windows::UI::Xaml::DependencyProperty^ imageSourceProperty;

        Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;

    public:
        RadialGradientBrushSimulator();

        static property Windows::UI::Xaml::DependencyProperty^ GradientOriginProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return gradientOriginProperty; }
        };

        static property Windows::UI::Xaml::DependencyProperty^ InnerColorProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return innerColorProperty; }
        };

        static property Windows::UI::Xaml::DependencyProperty^ OuterColorProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return outerColorProperty; }
        };

        static property Windows::UI::Xaml::DependencyProperty^ ClipToEllipseProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return clipToEllipseProperty; }
        };

        static property Windows::UI::Xaml::DependencyProperty^ ImageSourceProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return imageSourceProperty; }
        };

        property Windows::Foundation::Point GradientOrigin
        {
            void set(Windows::Foundation::Point value) { SetValue(GradientOriginProperty, value); }
            Windows::Foundation::Point get() { return (Windows::Foundation::Point)GetValue(GradientOriginProperty); }
        };

        property Windows::UI::Color InnerColor
        {
            void set(Windows::UI::Color value) { SetValue(InnerColorProperty, value); }
            Windows::UI::Color get() { return (Windows::UI::Color)GetValue(InnerColorProperty); }
        };

        property Windows::UI::Color OuterColor
        {
            void set(Windows::UI::Color value) { SetValue(OuterColorProperty, value); }
            Windows::UI::Color get() { return (Windows::UI::Color)GetValue(OuterColorProperty); }
        };

        property bool ClipToEllipse
        {
            void set(bool value) { SetValue(ClipToEllipseProperty, value); }
            bool get() { return (bool)GetValue(ClipToEllipseProperty); }
        }

        property Windows::UI::Xaml::Media::ImageSource^ ImageSource
        {
            Windows::UI::Xaml::Media::ImageSource^ get() { return dynamic_cast<Windows::UI::Xaml::Media::ImageSource^>(GetValue(ImageSourceProperty)); }
        }

    private:
        void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        static void OnPropertyChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void RefreshBitmap();
    };
}
