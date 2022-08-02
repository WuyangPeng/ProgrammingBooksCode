//
// SplitContainer.xaml.h
// Declaration of the SplitContainer class
//

#pragma once

#include "pch.h"
#include "SplitContainer.g.h"

namespace XamlCruncher
{
    public ref class SplitContainer sealed
    {
    private:
        // Dependency property overhead
        static Windows::UI::Xaml::DependencyProperty^ child1Property;
        static Windows::UI::Xaml::DependencyProperty^ child2Property;
        static Windows::UI::Xaml::DependencyProperty^ swapChildrenProperty;
        static Windows::UI::Xaml::DependencyProperty^ orientationProperty;
        static Windows::UI::Xaml::DependencyProperty^ minimumSizeProperty;

    public:
        // Constructor
        SplitContainer();

        // Dependency properties
        static property Windows::UI::Xaml::DependencyProperty^ Child1Property
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ Child2Property
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ SwapChildrenProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ OrientationProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ MinimumSizeProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        // Properties backed by dependency properties
        property Windows::UI::Xaml::UIElement^ Child1
        {
            void set(Windows::UI::Xaml::UIElement^);
            Windows::UI::Xaml::UIElement^ get();
        };
    
        property Windows::UI::Xaml::UIElement^ Child2
        {
            void set(Windows::UI::Xaml::UIElement^);
            Windows::UI::Xaml::UIElement^ get();
        };

        property Windows::UI::Xaml::Controls::Orientation Orientation
        {
            void set(Windows::UI::Xaml::Controls::Orientation);
            Windows::UI::Xaml::Controls::Orientation get();
        };

        property bool SwapChildren
        {
            void set(bool);
            bool get();
        };

        property double MinimumSize
        {
            void set(double);
            double get();
        };

     private:
        double grid1Size;
        double grid2Size;

        // Property changed handlers
        static void OnChildChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnChildInstanceChanged(Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

        static void OnOrientationChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnOrientationInstanceChanged(Windows::UI::Xaml::Controls::Orientation oldOrientation, Windows::UI::Xaml::Controls::Orientation newOrientation);

        static void OnSwapChildrenChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnSwapChildrenInstanceChanged(bool oldValue, bool newValue);

        static void OnMinSizeChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnMinSizeInstanceChanged(double oldValue, double newValue);

        // Thumb event handlers
        void OnThumbDragStarted(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::DragStartedEventArgs^ args);
        void OnThumbDragDelta(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::DragDeltaEventArgs^ args);
    };
}
