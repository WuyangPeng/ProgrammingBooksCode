#include "pch.h"
#include "RgbViewModel.h"

using namespace ColorScrollWithViewModel;

using namespace Platform;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Media;

RgbViewModel::RgbViewModel()
{
    this->color = ColorHelper::FromArgb(255, 0, 0, 0);
}

void RgbViewModel::Red::set(double value)
{
    if (red != value)
    {
        red = value;
        OnPropertyChanged("Red");
        Calculate();
    }
}

double RgbViewModel::Red::get()
{
    return red;
}

void RgbViewModel::Green::set(double value)
{
    if (green != value)
    {
        green = value;
        OnPropertyChanged("Green");
        Calculate();
    }
}

double RgbViewModel::Green::get()
{
    return green;
}

void RgbViewModel::Blue::set(double value)
{
    if (blue != value)
    {
        blue = value;
        OnPropertyChanged("Blue");
        Calculate();
    }
}

double RgbViewModel::Blue::get()
{
    return blue;
}

Color RgbViewModel::Color::get()
{
    return color;
}

void RgbViewModel::Calculate()
{
    this->color = ColorHelper::FromArgb(255, unsigned char(this->Red), 
                                             unsigned char(this->Green), 
                                             unsigned char(this->Blue));
    OnPropertyChanged("Color");
}

void RgbViewModel::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}
