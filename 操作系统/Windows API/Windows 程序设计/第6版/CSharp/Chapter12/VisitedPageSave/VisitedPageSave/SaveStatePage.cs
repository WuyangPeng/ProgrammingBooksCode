using System.Collections.Generic;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace VisitedPageSave
{
    public class SaveStatePage : Page
    {
        protected Dictionary<string, object> pageState;

        static protected Dictionary<int, Dictionary<string, object>> pages =
                                new Dictionary<int, Dictionary<string, object>>();

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
