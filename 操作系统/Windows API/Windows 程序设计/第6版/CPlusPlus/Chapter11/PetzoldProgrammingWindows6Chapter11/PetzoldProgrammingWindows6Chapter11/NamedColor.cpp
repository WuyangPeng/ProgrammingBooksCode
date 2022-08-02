#include "pch.h"
#include "NamedColor.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;

// C# assembly
using namespace ReflectionHelper;

IIterable<NamedColor^>^ NamedColor::all = nullptr;

IIterable<NamedColor^>^ NamedColor::All::get()
{
    if (all == nullptr)
    {
       Vector<NamedColor^>^ colorVector = ref new Vector<NamedColor^>();

        // Implemented in C# assembly ReflectionHelper
        TypeInformation^ typeInfo = ref new TypeInformation(Colors::typeid);
        IIterable<PropertyInformation^>^ properties = typeInfo->DeclaredProperties;

        for each (PropertyInformation^ property in properties)
        {
            NamedColor^ namedColor = ref new NamedColor();
            namedColor->name = property->Name;
            namedColor->color = (Windows::UI::Color)property->GetValue(nullptr);
            colorVector->Append(namedColor);
        }

        all = colorVector;
    }
    return all;
}
