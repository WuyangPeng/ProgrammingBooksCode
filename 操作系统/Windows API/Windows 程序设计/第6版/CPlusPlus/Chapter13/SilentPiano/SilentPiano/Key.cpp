#include "pch.h"
#include "Key.h"

using namespace SilentPiano;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

DependencyProperty^ Key::isPressedProperty = 
    DependencyProperty::Register("IsPressed", 
                                 TypeName(bool::typeid), 
                                 TypeName(Key::typeid),
                                 ref new PropertyMetadata(false, 
                                 ref new PropertyChangedCallback(OnIsPressedChanged)));

Key::Key()
{
    DefaultStyleKey = "SilentPiano.Key";
    pointerList = ref new Vector<unsigned int>();
}

DependencyProperty^ Key::IsPressedProperty::get()
{
    return isPressedProperty;
}

void Key::IsPressed::set(bool angle)
{
    SetValue(IsPressedProperty, angle);
}

bool Key::IsPressed::get()
{
    return (bool)GetValue(IsPressedProperty);
}

void Key::OnPointerEntered(PointerRoutedEventArgs^ args)
{
    if (args->Pointer->IsInContact)
        AddToList(args->Pointer->PointerId);
}

void Key::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    AddToList(args->Pointer->PointerId);
}

void Key::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    RemoveFromList(args->Pointer->PointerId);
}

void Key::OnPointerExited(PointerRoutedEventArgs^ args)
{
    RemoveFromList(args->Pointer->PointerId);
}

void Key::AddToList(unsigned int id)
{
    unsigned int index;
    if (!pointerList->IndexOf(id, &index))
        pointerList->Append(id);

    CheckList();
}

void Key::RemoveFromList(unsigned int id)
{
    unsigned int index;
    if (pointerList->IndexOf(id, &index))
        pointerList->RemoveAt(index);

    CheckList();
}

void Key::CheckList()
{
    this->IsPressed = pointerList->Size > 0;
}

void Key::OnIsPressedChanged(DependencyObject^ obj,
                             DependencyPropertyChangedEventArgs^ args)
{
    VisualStateManager::GoToState(dynamic_cast<Key^>(obj), 
                    (bool)args->NewValue ? "Pressed" : "Normal", false);
}
