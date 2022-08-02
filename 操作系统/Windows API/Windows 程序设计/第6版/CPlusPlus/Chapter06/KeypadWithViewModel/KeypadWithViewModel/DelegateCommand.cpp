#include "pch.h"
#include "DelegateCommand.h"

using namespace Platform;
using namespace Windows::Foundation;

using namespace KeypadWithViewModel;

// Two constructors
DelegateCommand::DelegateCommand(ExecuteDelegate^ execute, CanExecuteDelegate^ canExecute)
{
    executeAction = execute;
    canExecuteAction = canExecute;
}

DelegateCommand::DelegateCommand(ExecuteDelegate^ execute)
{
    executeAction = execute;
    canExecuteAction = ref new CanExecuteDelegate(this, &DelegateCommand::AlwaysCanExecute);
}

// Methods required by ICommand
void DelegateCommand::Execute(Object^ param)
{
    executeAction(param);
}

bool DelegateCommand::CanExecute(Object^ param)
{
    return canExecuteAction(param);
}

// Method required by IDelegateCommand
void DelegateCommand::RaiseCanExecuteChanged()
{
    CanExecuteChanged(this, nullptr);
}

// Default CanExecute method
bool DelegateCommand::AlwaysCanExecute(Object^ param)
{
    return true;
}
