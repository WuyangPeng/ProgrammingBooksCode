#include "pch.h"

namespace KeypadWithViewModel
{
    public delegate void ExecuteDelegate(Platform::Object^ param);
    public delegate bool CanExecuteDelegate(Platform::Object^ param);

    public interface class IDelegateCommand : Windows::UI::Xaml::Input::ICommand
    {
        void RaiseCanExecuteChanged();
    };
}
