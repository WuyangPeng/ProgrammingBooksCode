using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleFinalize
{
    // Override System.Object.Finalize() via finalizer syntax.
    class MyResourceWrapper
    {
        ~MyResourceWrapper()
        {
            // Clean up unmanaged resources here.

            // Beep when destroyed (testing purposes only!)
            Console.Beep();
        }
    }
}
