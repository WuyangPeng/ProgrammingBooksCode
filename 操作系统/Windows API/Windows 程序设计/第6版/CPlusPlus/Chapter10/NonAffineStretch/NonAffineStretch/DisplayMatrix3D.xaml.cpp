//
// DisplayMatrix3D.xaml.cpp
// Implementation of the DisplayMatrix3D class
//

#include "pch.h"
#include "DisplayMatrix3D.xaml.h"

using namespace NonAffineStretch;

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
using namespace Windows::UI::Xaml::Media::Media3D;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ DisplayMatrix3D::matrix3DProperty = 
    DependencyProperty::Register("Matrix3D", 
                                 TypeName(Windows::UI::Xaml::Media::Media3D::Matrix3D::typeid), 
                                 TypeName(DisplayMatrix3D::typeid),
                                 ref new PropertyMetadata(Windows::UI::Xaml::Media::Media3D::Matrix3D(),
                                 ref new PropertyChangedCallback(OnPropertyChanged)));

DisplayMatrix3D::DisplayMatrix3D()
{
    InitializeComponent();
}

DependencyProperty^ DisplayMatrix3D::Matrix3DProperty::get()
{
    return matrix3DProperty;
}

void DisplayMatrix3D::Matrix3D::set(Windows::UI::Xaml::Media::Media3D::Matrix3D matrix3D)
{
    SetValue(Matrix3DProperty, matrix3D);
}

Windows::UI::Xaml::Media::Media3D::Matrix3D DisplayMatrix3D::Matrix3D::get()
{
    return (Windows::UI::Xaml::Media::Media3D::Matrix3D)GetValue(Matrix3DProperty);
}

void DisplayMatrix3D::OnPropertyChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<DisplayMatrix3D^>(obj)->OnPropertyChangedInstance(args);
}

void DisplayMatrix3D::OnPropertyChangedInstance(DependencyPropertyChangedEventArgs^ args)
{
    m11->Text = Format(this->Matrix3D.M11, 3);
    m12->Text = Format(this->Matrix3D.M12, 3);
    m13->Text = Format(this->Matrix3D.M13, 3);
    m14->Text = Format(this->Matrix3D.M14, 6);

    m21->Text = Format(this->Matrix3D.M21, 3);
    m22->Text = Format(this->Matrix3D.M22, 3);
    m23->Text = Format(this->Matrix3D.M23, 3);
    m24->Text = Format(this->Matrix3D.M24, 6);

    m31->Text = Format(this->Matrix3D.M31, 3);
    m32->Text = Format(this->Matrix3D.M32, 3);
    m33->Text = Format(this->Matrix3D.M33, 3);
    m34->Text = Format(this->Matrix3D.M34, 6);

    m41->Text = Format(this->Matrix3D.OffsetX, 0);
    m42->Text = Format(this->Matrix3D.OffsetY, 0);
    m43->Text = Format(this->Matrix3D.OffsetZ, 0);
    m44->Text = Format(this->Matrix3D.M44, 0);
}

String^ DisplayMatrix3D::Format(double number, int decimals)
{
    wchar_t str[16];
    swprintf(str, sizeof(str) / sizeof(str[0]), L"%.*f", decimals, number);
    return ref new String(str);
}