#pragma once

#include "pch.h"
#include "IDelegateCommand.h"

namespace KeypadWithViewModel
{
    public ref class DelegateCommand sealed : IDelegateCommand
    {
    public:
        DelegateCommand(ExecuteDelegate^ execute, CanExecuteDelegate^ canExecute);
        DelegateCommand(ExecuteDelegate^ execute);

        virtual event Windows::Foundation::EventHandler<Platform::Object^>^ CanExecuteChanged;

        virtual void Execute(Platform::Object^ parameter);
        virtual bool CanExecute(Platform::Object^ parameter);
        virtual void RaiseCanExecuteChanged();

    private:
        ExecuteDelegate^ executeAction;
        CanExecuteDelegate^ canExecuteAction;
        bool AlwaysCanExecute(Platform::Object^);
    };
}
