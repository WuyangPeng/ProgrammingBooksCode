#pragma once

#include "pch.h"
#include "DelegateCommand.h"

namespace KeypadWithViewModel
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class KeypadViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        std::wstring inputString;
        std::wstring displayText;
        IDelegateCommand^ addCharacterCommand;
        IDelegateCommand^ deleteCharacterCommand;
        void ExecuteAddCharacter(Platform::Object^ param);
        void ExecuteDeleteCharacter(Platform::Object^ param);
        bool CanExecuteDeleteCharacter(Platform::Object^ param);
        void NewInputString(bool previousCanExecuteDeleteChar);
        std::wstring FormatText(std::wstring str);

    public:
        KeypadViewModel();

        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ InputString
        {
            Platform::String^ get();
        }

        property Platform::String^ DisplayText
        {
            Platform::String^ get();
        }

        property IDelegateCommand^ AddCharacterCommand
        {
            IDelegateCommand^ get();
        };

        property IDelegateCommand^ DeleteCharacterCommand
        {
            IDelegateCommand^ get();
        };

    protected:
        void OnPropertyChanged(Platform::String^ propertyName);
    };
}
