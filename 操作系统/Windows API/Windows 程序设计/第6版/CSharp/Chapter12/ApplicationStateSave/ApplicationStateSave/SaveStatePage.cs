using System;
using System.Collections.Generic;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace ApplicationStateSave
{
    public class SaveStatePage : Page
    {
        protected Dictionary<string, object> pageState;

        static protected Dictionary<int, Dictionary<string, object>> pages =
                                new Dictionary<int, Dictionary<string, object>>();

        static SaveStatePage()
        {
            // Set handler for Suspending event
            Application.Current.Suspending += OnApplicationSuspending;

            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

            // Loop through containers, one for each page in the back stack
            foreach (ApplicationDataContainer container in appData.Containers.Values)
            {
                // Create a page state dictionary for that page
                Dictionary<string, object> pageState = new Dictionary<string, object>();

                // Fill it up with saved values
                foreach (string key in container.Values.Keys)
                {
                    pageState.Add(key, container.Values[key]);
                }

                // Save in static dictionary
                int pageKey = Int32.Parse(container.Name);
                pages[pageKey] = pageState;
            }
        }

        static void OnApplicationSuspending(object sender, SuspendingEventArgs args)
        {
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

            foreach (int pageKey in pages.Keys)
            {
                // Create container based on location within back stack
                string containerName = pageKey.ToString();

                // Get container with that name and clear it
                ApplicationDataContainer container = 
                    appData.CreateContainer(containerName, 
                                            ApplicationDataCreateDisposition.Always);
                container.Values.Clear();

                // Save settings for each page in that container
                foreach (string key in pages[pageKey].Keys)
                    container.Values.Add(key, pages[pageKey][key]);
            }
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            if (args.NavigationMode == NavigationMode.New)
            {
                // Construct a dictionary key
                int pageKey = this.Frame.BackStackDepth;

                // Remove page key and higher page keys
                for (int key = pageKey; pages.Remove(key); key++) ;

                // Create a new page state dictionary and save it
                pageState = new Dictionary<string, object>();
                pages.Add(pageKey, pageState);
            }

            base.OnNavigatedTo(args);
        }
    }
}