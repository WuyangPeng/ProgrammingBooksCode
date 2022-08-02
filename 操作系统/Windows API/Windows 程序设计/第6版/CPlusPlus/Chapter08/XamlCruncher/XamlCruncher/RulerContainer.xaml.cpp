//
// RulerContainer.xaml.cpp
// Implementation of the RulerContainer class
//

#include "pch.h"
#include "RulerContainer.xaml.h"

using namespace XamlCruncher;

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
using namespace Windows::UI::Xaml::Shapes;

RulerContainer::RulerContainer()
{
    InitializeComponent();
}

const double RulerContainer::RULER_WIDTH = 12;

DependencyProperty^ RulerContainer::childProperty = 
    DependencyProperty::Register("Child", 
                                 TypeName(UIElement::typeid), 
                                 TypeName(RulerContainer::typeid),
                                 ref new PropertyMetadata(nullptr,
                                 ref new PropertyChangedCallback(OnChildChanged)));
    
DependencyProperty^ RulerContainer::showRulerProperty = 
    DependencyProperty::Register("ShowRuler", 
                                 TypeName(Boolean::typeid), 
                                 TypeName(RulerContainer::typeid),
                                 ref new PropertyMetadata(nullptr,
                                 ref new PropertyChangedCallback(OnShowRulerChanged)));

DependencyProperty^ RulerContainer::showGridLinesProperty = 
    DependencyProperty::Register("ShowGridLines", 
                                 TypeName(Boolean::typeid), 
                                 TypeName(RulerContainer::typeid),
                                 ref new PropertyMetadata(nullptr,
                                 ref new PropertyChangedCallback(OnShowGridLinesChanged)));

DependencyProperty^ RulerContainer::ChildProperty::get()
{
    return childProperty;
}

DependencyProperty^ RulerContainer::ShowRulerProperty::get()
{
    return showRulerProperty;
}

DependencyProperty^ RulerContainer::ShowGridLinesProperty::get()
{
    return showGridLinesProperty;
}

void RulerContainer::Child::set(UIElement^ value)
{
    SetValue(ChildProperty, value);
}

UIElement^ RulerContainer::Child::get()
{
    return safe_cast<UIElement^>(GetValue(ChildProperty));
}

void RulerContainer::ShowRuler::set(bool value)
{
    SetValue(ShowRulerProperty, value); 
}

bool RulerContainer::ShowRuler::get()
{
    return (bool)GetValue(ShowRulerProperty);
}

void RulerContainer::ShowGridLines::set(bool value)
{
    SetValue(ShowGridLinesProperty, value); 
}

bool RulerContainer::ShowGridLines::get()
{
    return (bool)GetValue(ShowGridLinesProperty);
}

void RulerContainer::OnChildChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<RulerContainer^>(obj)->border->Child = dynamic_cast<UIElement^>(args->NewValue);
}

void RulerContainer::OnShowRulerChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<RulerContainer^>(obj)->RedrawRuler();
}

void RulerContainer::OnShowGridLinesChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<RulerContainer^>(obj)->RedrawGridLines();
}

void RulerContainer::OnGridSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    RedrawRuler();
    RedrawGridLines();
}

void RulerContainer::RedrawGridLines()
{
    gridLinesGrid->Children->Clear();

    if (!this->ShowGridLines)
        return;

    // Vertical grid liens every 1/4"
    for (double x = 24; x < gridLinesGrid->ActualWidth; x+=24)
    {
        Line^ line = ref new Line();
        line->X1 = x;
        line->Y1 = 0;
        line->X2 = x;
        line->Y2 = gridLinesGrid->ActualHeight;
        line->Stroke = this->Foreground;
        line->StrokeThickness = (int)x % 96 == 0 ? 1 : 0.5;
        gridLinesGrid->Children->Append(line);
    }

    // Horizontal grid lines every 1/4"
    for (double y = 24; y < gridLinesGrid->ActualHeight; y+=24)
    {
        Line^ line = ref new Line();
        line->X1 = 0;
        line->Y1 = y;
        line->X2 = gridLinesGrid->ActualWidth;
        line->Y2 = y;
        line->Stroke = this->Foreground;
        line->StrokeThickness = (int)y % 96 == 0 ? 1 : 0.5;
        gridLinesGrid->Children->Append(line);
    }
}

void RulerContainer::RedrawRuler()
{
    rulerCanvas->Children->Clear();

    if (!this->ShowRuler)
    {
        innerGrid->Margin = ThicknessHelper::FromUniformLength(0);
        return;
    }

    innerGrid->Margin = ThicknessHelper::FromLengths(RULER_WIDTH, RULER_WIDTH, 0, 0);

    // Ruler across the top
    for (double x = 0; x < gridLinesGrid->ActualWidth - RULER_WIDTH; x += 12)
    {
        // Numbers every inch
        if (x > 0 && (int)x % 96 == 0)
        {
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = (x / 96).ToString();
            txtblk->FontSize = RULER_WIDTH - 2;
            Size size = Size(0, 0);
            txtblk->Measure(size);
            Canvas::SetLeft(txtblk, RULER_WIDTH + x - txtblk->ActualWidth / 2);
            Canvas::SetTop(txtblk, 0);
            rulerCanvas->Children->Append(txtblk);
        }
        // Tick marks every 1/8"
        else
        {
            Line^ line = ref new Line();
            line->X1 = RULER_WIDTH + x;
            line->Y1 = (int)x % 48 == 0 ? 2 : 4;
            line->X2 = RULER_WIDTH + x;
            line->Y2 = (int)x % 48 == 0 ? RULER_WIDTH - 2 : RULER_WIDTH - 4;
            line->Stroke = this->Foreground;
            line->StrokeThickness = 1;
            rulerCanvas->Children->Append(line);
        }
    }

    // Heavy line underneath the tick marks
    Line^ topLine = ref new Line();
    topLine->X1 = RULER_WIDTH - 1;
    topLine->Y1 = RULER_WIDTH - 1;
    topLine->X2 = rulerCanvas->ActualWidth;
    topLine->Y2 = RULER_WIDTH - 1;
    topLine->Stroke = this->Foreground;
    topLine->StrokeThickness = 2;
    rulerCanvas->Children->Append(topLine);

    // Ruler down the left side
    for (double y = 0; y < gridLinesGrid->ActualHeight - RULER_WIDTH; y += 12)
    {
        // Numbers every inch
        if (y > 0 && (int)y % 96 == 0)
        {
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = (y / 96).ToString();
            txtblk->FontSize = RULER_WIDTH - 2;
            Size size = Size(0, 0);
            txtblk->Measure(size);
            Canvas::SetLeft(txtblk, 2);
            Canvas::SetTop(txtblk, RULER_WIDTH + y - txtblk->ActualHeight / 2);
            rulerCanvas->Children->Append(txtblk);
        }
        // Tick marks every 1/8"
        else
        {
            Line^ line = ref new Line();
            line->X1 = (int)y % 48 == 0 ? 2 : 4;
            line->Y1 = RULER_WIDTH + y;
            line->X2 = (int)y % 48 == 0 ? RULER_WIDTH - 2 : RULER_WIDTH - 4;
            line->Y2 = RULER_WIDTH + y;
            line->Stroke = this->Foreground;
            line->StrokeThickness = 1;
            rulerCanvas->Children->Append(line);
        }
    }

    // Heavy line to the left of the tick marks
    Line^ leftLine = ref new Line();
    leftLine->X1 = RULER_WIDTH - 1;
    leftLine->Y1 = RULER_WIDTH - 1;
    leftLine->X2 = RULER_WIDTH - 1;
    leftLine->Y2 = rulerCanvas->ActualHeight;
    leftLine->Stroke = this->Foreground;
    leftLine->StrokeThickness = 2;
    rulerCanvas->Children->Append(leftLine);
}