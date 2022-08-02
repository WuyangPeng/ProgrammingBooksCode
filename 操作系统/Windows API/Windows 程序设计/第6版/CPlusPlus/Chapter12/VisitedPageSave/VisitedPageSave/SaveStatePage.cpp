#include "pch.h"
#include "SaveStatePage.h"

using namespace VisitedPageSave;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Navigation;

Map<int, IMap<String^, Object^>^>^ SaveStatePage::pages = ref new Map<int, IMap<String^, Object^>^>();

void SaveStatePage::OnNavigatedTo(NavigationEventArgs^ args)
{
    if (args->NavigationMode == NavigationMode::New)
    {
        // Construct a dictionary key
        int pageKey = this->Frame->BackStackDepth;

        // Remove page key and higher page keys
        for (int key = pageKey; SaveStatePage::Pages->HasKey(key); key++)
            SaveStatePage::Pages->Remove(key);

        // Create a new page state dictionary and save it
        this->PageState = ref new Map<String^, Object^>();
        SaveStatePage::Pages->Insert(pageKey, this->PageState);
    }
}