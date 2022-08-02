#pragma once

namespace PetzoldProgrammingWindows6Chapter11
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class UniformGridBase : Windows::UI::Xaml::Controls::Panel
    {
    internal:
        UniformGridBase() {}

    private:
        static Windows::UI::Xaml::DependencyProperty^ rowsProperty;
        static Windows::UI::Xaml::DependencyProperty^ columnsProperty;
        static Windows::UI::Xaml::DependencyProperty^ orientationProperty;

    public:
        static property Windows::UI::Xaml::DependencyProperty^ RowsProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return rowsProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ColumnsProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return columnsProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ OrientationProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return orientationProperty; }
        }

        property int Rows
        {
            void set(int value) { SetValue(RowsProperty, value); }
            int get() { return (int)GetValue(RowsProperty); }
        }

        property int Columns
        {
            void set(int value) { SetValue(ColumnsProperty, value); }
            int get() { return (int)GetValue(ColumnsProperty); }
        }

        property Windows::UI::Xaml::Controls::Orientation Orientation
        {
            void set(Windows::UI::Xaml::Controls::Orientation value) { SetValue(OrientationProperty, value); }
            Windows::UI::Xaml::Controls::Orientation get() { return (Windows::UI::Xaml::Controls::Orientation)GetValue(OrientationProperty); }
        }

    private:
        static void OnPropertyChanged(Windows::UI::Xaml::DependencyObject^ obj, 
                                      Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

    protected:
        // Set by MeasureOverride, used in ArrangeOverride
        property int rows;
        property int cols;

        virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize) override;
        virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size finalSize) override;
    };
}