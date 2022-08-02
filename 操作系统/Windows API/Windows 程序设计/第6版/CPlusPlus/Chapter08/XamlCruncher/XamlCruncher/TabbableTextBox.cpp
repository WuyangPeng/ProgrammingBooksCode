#include "pch.h"
#include "TabbableTextBox.h"

using namespace XamlCruncher;

using namespace Platform;
using namespace Windows::System;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;

DependencyProperty^ TabbableTextBox::tabSpacesProperty = 
    DependencyProperty::Register("TabSpaces", 
                                 TypeName(int::typeid), 
                                 TypeName(TabbableTextBox::typeid),
                                 ref new PropertyMetadata(4));

TabbableTextBox::TabbableTextBox()
{
    KeyDown += ref new KeyEventHandler(this, &TabbableTextBox::OnTabKeyDown);
}
    
DependencyProperty^ TabbableTextBox::TabSpacesProperty::get()
{
    return tabSpacesProperty;
}

void TabbableTextBox::TabSpaces::set(int value)
{
    SetValue(TabSpacesProperty, value);
}

int TabbableTextBox::TabSpaces::get()
{
    return (int)GetValue(TabSpacesProperty);
}

void TabbableTextBox::OnTabKeyDown(Object^ sender, KeyRoutedEventArgs^ args)
{
    this->IsModified = true;

    if (args->Key == VirtualKey::Tab)
    {
        int line, col;
        GetPositionFromIndex(this->SelectionStart, &line, &col);
        int insertCount = this->TabSpaces - col % this->TabSpaces;
        wchar_t* insertSpace = new wchar_t[1 + insertCount];

        int i = 0;
        while (i < insertCount)
            insertSpace[i++] = ' ';

        insertSpace[i] = '\0';

        this->SelectedText = ref new String(insertSpace);
        delete[] insertSpace;

        this->SelectionStart += insertCount;
        this->SelectionLength = 0;
        args->Handled = true;
    }
}

void TabbableTextBox::GetPositionFromIndex(unsigned int index, int* line, int* col)
{
    if (index > this->Text->Length())
    {
        *line = *col = -1;
        return;
    }

    String^ str = this->Text;
    const wchar_t* text = str->Data();
    *line = *col = 0;
    unsigned int i = 0;

    while (i < index)
    {
        if (text[i] == '\n')
        {
            (*line)++;
            *col = 0;
        }
        else if (text[i] == '\r')
        {
            index++;
        }
        else
        {
            (*col)++;
        };
        i++;
    }
}
