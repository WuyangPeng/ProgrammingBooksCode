//
// Block.xaml.cpp
// Implementation of the Block class
//

#include "pch.h"
#include "Block.xaml.h"

using namespace AlphabetBlocks;

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
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ Block::textProperty = 
    DependencyProperty::Register("Text", 
                                 TypeName(String::typeid), 
                                 TypeName(Block::typeid), 
                                 ref new PropertyMetadata("?"));

Block::Block()
{
    InitializeComponent();
}

DependencyProperty^ Block::TextProperty::get()
{
    return textProperty;
}

String^ Block::Text::get()
{
    return dynamic_cast<String^>(GetValue(TextProperty));
}

void Block::Text::set(String^ value)
{
    SetValue(TextProperty, value);
}

int Block::ZIndex::get()
{
    static int zindex = 0;
    return ++zindex;
}

void Block::OnThumbDragStarted(Object^ sender, DragStartedEventArgs^ args)
{
    Canvas::SetZIndex(this, Block::ZIndex);
}

void Block::OnThumbDragDelta(Object^ sender, DragDeltaEventArgs^ args)
{
    Canvas::SetLeft(this, Canvas::GetLeft(this) + args->HorizontalChange);
    Canvas::SetTop(this, Canvas::GetTop(this) + args->VerticalChange);
}
