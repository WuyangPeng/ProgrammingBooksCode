//
// RulerContainer.xaml.h
// Declaration of the RulerContainer class
//

#pragma once

#include "pch.h"
#include "RulerContainer.g.h"

namespace XamlCruncher
{
    public ref class RulerContainer sealed
    {
    public:
        RulerContainer();

    private:
        static const double RULER_WIDTH;

        static Windows::UI::Xaml::DependencyProperty^ childProperty;
        static Windows::UI::Xaml::DependencyProperty^ showRulerProperty;
        static Windows::UI::Xaml::DependencyProperty^ showGridLinesProperty;

    public:
        static property Windows::UI::Xaml::DependencyProperty^ ChildProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        static property Windows::UI::Xaml::DependencyProperty^ ShowRulerProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        static property Windows::UI::Xaml::DependencyProperty^ ShowGridLinesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property Windows::UI::Xaml::UIElement^ Child
        {
            void set(Windows::UI::Xaml::UIElement^);
            Windows::UI::Xaml::UIElement^ get();
        }

        property bool ShowRuler
        {
            void set(bool);
            bool get();
        }

        property bool ShowGridLines
        {
            void set(bool);
            bool get();
        }

    private:
        static void OnChildChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        static void OnShowRulerChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        static void OnShowGridLinesChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

        void OnGridSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void RedrawGridLines();
        void RedrawRuler();
    };
}
