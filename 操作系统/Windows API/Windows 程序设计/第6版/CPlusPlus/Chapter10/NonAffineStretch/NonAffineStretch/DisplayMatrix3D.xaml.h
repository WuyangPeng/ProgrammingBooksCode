//
// DisplayMatrix3D.xaml.h
// Declaration of the DisplayMatrix3D class
//

#pragma once

#include "DisplayMatrix3D.g.h"

namespace NonAffineStretch
{
    public ref class DisplayMatrix3D sealed
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ matrix3DProperty;

    public:
        DisplayMatrix3D();

        static property Windows::UI::Xaml::DependencyProperty^ Matrix3DProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property Windows::UI::Xaml::Media::Media3D::Matrix3D Matrix3D
        {
            void set(Windows::UI::Xaml::Media::Media3D::Matrix3D);
            Windows::UI::Xaml::Media::Media3D::Matrix3D get();
        }

    private:
        static void OnPropertyChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnPropertyChangedInstance(Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        Platform::String^ Format(double number, int decimals);
    };
}
