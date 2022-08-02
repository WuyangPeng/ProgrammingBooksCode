#pragma once

#include "pch.h"

namespace AnimatedPieSlice
{
    public ref class PieSlice sealed : Windows::UI::Xaml::Shapes::Path
    {
    private:
        Windows::UI::Xaml::Media::PathFigure^ pathFigure;
        Windows::UI::Xaml::Media::LineSegment^ lineSegment;
        Windows::UI::Xaml::Media::ArcSegment^ arcSegment;

        // Dependency property overhead
        static Windows::UI::Xaml::DependencyProperty^ centerProperty;
        static Windows::UI::Xaml::DependencyProperty^ radiusProperty;
        static Windows::UI::Xaml::DependencyProperty^ startAngleProperty;
        static Windows::UI::Xaml::DependencyProperty^ sweepAngleProperty;

    public:
        // Constructor
        PieSlice();

        // Dependency properties
        static property Windows::UI::Xaml::DependencyProperty^ CenterProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ RadiusProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ StartAngleProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        static property Windows::UI::Xaml::DependencyProperty^ SweepAngleProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        // Properties backed by dependency properties
        property Windows::Foundation::Point Center
        {
            void set(Windows::Foundation::Point);
            Windows::Foundation::Point get();
        };
    
        property double Radius
        {
            void set(double);
            double get();
        };

        property double StartAngle
        {
            void set(double);
            double get();
        };

        property double SweepAngle
        {
            void set(double);
            double get();
        };

     private:
        static void OnPropertyChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void UpdateValues();
    };
}
