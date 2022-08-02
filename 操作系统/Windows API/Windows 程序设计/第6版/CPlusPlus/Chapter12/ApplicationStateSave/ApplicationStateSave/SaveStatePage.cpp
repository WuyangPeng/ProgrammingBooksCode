#include "pch.h"
#include "SaveStatePage.h"

using namespace ApplicationStateSave;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;

SaveStatePage::SaveStatePage()
{
    // Do this for only the first instance
    if (SaveStatePage::Pages == nullptr)
    {
        SaveStatePage::Pages = ref new Map<int, IMap<String^, Object^>^>();

        // Set handler for Suspending event
        Application::Current->Suspending += ref new SuspendingEventHandler(&SaveStatePage::OnApplicationSuspending);

        ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

        // Loop through containers, one for each page in the back stack
        for each (IKeyValuePair<String^, ApplicationDataContainer^>^ containerPairs in appData->Containers)
        {
            // Create a page state map for that page
            Map<String^, Object^>^ pageState = ref new Map<String^, Object^>();

            // Fill it up with saved values
            for each (IKeyValuePair<String^, Object^>^ statePairs in containerPairs->Value->Values)
            {
                pageState->Insert(statePairs->Key, statePairs->Value);
            }

            // Save in static map
            int pageKey = _wtoi(containerPairs->Key->Data());
            SaveStatePage::Pages->Insert(pageKey, pageState);
        }
    }
}

void SaveStatePage::OnApplicationSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

    for each (IKeyValuePair<int, IMap<String^, Object^>^>^ pagesPair in SaveStatePage::Pages)
    {
        // Create container based on location within back stack
        String^ containerName = pagesPair->Key.ToString();

        // Get container with that name and clear it
        ApplicationDataContainer^ container = 
                appData->CreateContainer(containerName, ApplicationDataCreateDisposition::Always);

        container->Values->Clear();

        // Save setting for each page in that container
        for each (IKeyValuePair<String^, Object^>^ statePairs in pagesPair->Value)
            container->Values->Insert(statePairs->Key, statePairs->Value);
    }
}

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