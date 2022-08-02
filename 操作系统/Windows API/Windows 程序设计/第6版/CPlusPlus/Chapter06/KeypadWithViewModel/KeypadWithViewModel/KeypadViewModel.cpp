#include "pch.h"
#include "KeypadViewModel.h"

using namespace Windows::UI::Xaml::Data;
using namespace Platform;

using namespace KeypadWithViewModel;

// Constructor
KeypadViewModel::KeypadViewModel()
{
    inputString = L"";
    displayText = L"";

    addCharacterCommand = ref new DelegateCommand(
                                        ref new ExecuteDelegate(this, &KeypadViewModel::ExecuteAddCharacter));

    deleteCharacterCommand = ref new DelegateCommand(
                                        ref new ExecuteDelegate(this, &KeypadViewModel::ExecuteDeleteCharacter), 
                                        ref new CanExecuteDelegate(this, &KeypadViewModel::CanExecuteDeleteCharacter));
}

// Public properties
String^ KeypadViewModel::InputString::get()
{
    return ref new String(inputString.c_str());
}

String^ KeypadViewModel::DisplayText::get()
{
    return ref new String(displayText.c_str());
}

// ICommand implementations
IDelegateCommand^ KeypadViewModel::AddCharacterCommand::get()
{
    return addCharacterCommand;
}

IDelegateCommand^ KeypadViewModel::DeleteCharacterCommand::get()
{
    return deleteCharacterCommand;
}

// Execute and CanExecute methods
void KeypadViewModel::ExecuteAddCharacter(Object^ param)
{
    const wchar_t * newChar = dynamic_cast<String^>(param)->Data();

    bool previousCanExecuteDeleteChar = CanExecuteDeleteCharacter(nullptr);
    this->inputString.append(newChar);
    NewInputString(previousCanExecuteDeleteChar);
}

void KeypadViewModel::ExecuteDeleteCharacter(Object^ param)
{
    bool previousCanExecuteDeleteChar = CanExecuteDeleteCharacter(nullptr);
    this->inputString = this->inputString.substr(0, this->inputString.length() - 1);
    NewInputString(previousCanExecuteDeleteChar);
}

bool KeypadViewModel::CanExecuteDeleteCharacter(Object^ param)
{
    return this->inputString.length() > 0;
}

// Private methods called when input string changes
void KeypadViewModel::NewInputString(bool previousCanExecuteDeleteChar)
{
    OnPropertyChanged("InputString");
    this->displayText = FormatText(inputString);
    OnPropertyChanged("DisplayText");

    if (previousCanExecuteDeleteChar != CanExecuteDeleteCharacter(nullptr))
        DeleteCharacterCommand->RaiseCanExecuteChanged();
}

std::wstring KeypadViewModel::FormatText(std::wstring str)
{
    std::wstring formatted = str;
    bool hasNonNumbers = str.find_first_of(L"*#") != str.npos;
    
    if (hasNonNumbers || str.length() < 4 || str.length() > 10)
    {
    }
    else if (str.length() < 8)
    {
        formatted = str.substr(0, 3)
                       .append(L"-")
                       .append(str.substr(3, str.length() - 3));
    }
    else
    {
        formatted = std::wstring(L"(").append(str.substr(0, 3))
                                      .append(L")")
                                      .append(str.substr(3, 3))
                                      .append(L"-")
                                      .append(str.substr(6, str.length() - 6));
    }
    return formatted;
}

void KeypadViewModel::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}

