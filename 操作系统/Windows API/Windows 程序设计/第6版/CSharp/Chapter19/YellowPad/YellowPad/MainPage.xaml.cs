using System.Collections.ObjectModel;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace YellowPad
{
    public sealed partial class MainPage : Page
    {
        ObservableCollection<InkFileManager> inkFileManagers =
                                                new ObservableCollection<InkFileManager>();
        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnMainPageLoaded;
            Application.Current.Suspending += OnApplicationSuspending;
        }

        void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            // Load application settings
            IPropertySet appData = ApplicationData.Current.LocalSettings.Values;

            // Get the page count
            int pageCount = 1;

            if (appData.ContainsKey("PageCount"))
                pageCount = (int)appData["PageCount"];

            // Create that many InkFileManager objects
            for (int i = 0; i < pageCount; i++)
                inkFileManagers.Add(new InkFileManager(i.ToString()));

            // Set the collection to the FlipView
            flipView.ItemsSource = inkFileManagers;

            // Set the SelectedIndex of the PageView
            if (appData.ContainsKey("PageIndex"))
                flipView.SelectedIndex = (int)appData["PageIndex"];
        }

        async void OnApplicationSuspending(object sender, SuspendingEventArgs args)
        {
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();

            // Save all the InkFileManager contents
            foreach (InkFileManager inkFileManager in inkFileManagers)
                await inkFileManager.SaveAsync();

            // Save the page count and current page index
            IPropertySet appData = ApplicationData.Current.LocalSettings.Values;
            appData["PageCount"] = inkFileManagers.Count;
            appData["PageIndex"] = flipView.SelectedIndex;

            deferral.Complete();
        }

        void OnFlipViewSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            // If at the end of the FlipView, add another item!
            if (flipView.SelectedIndex == flipView.Items.Count - 1)
                inkFileManagers.Add(new InkFileManager(flipView.Items.Count.ToString()));
        }

        void OnAppBarOpened(object sender, object args)
        {
            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;

            copyAppBarButton.IsEnabled = inkFileManager.IsAnythingSelected;
            cutAppBarButton.IsEnabled = inkFileManager.IsAnythingSelected;
            pasteAppBarButton.IsEnabled = inkFileManager.InkManager.CanPasteFromClipboard();
            deleteAppBarButton.IsEnabled = inkFileManager.IsAnythingSelected;

            if (!inkFileManager.IsAnythingSelected)
            {
                // Set initial selected item
                Size size = inkFileManager.InkDrawingAttributes.Size;
                penSizeComboBox.SelectedItem = (size.Width + size.Height) / 2;
                colorComboBox.SelectedItem = inkFileManager.InkDrawingAttributes.Color;
            }
            else
            {
                penSizeComboBox.SelectedItem = null;
                colorComboBox.SelectedItem = null;
            }
        }

        void OnCopyAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;
            inkFileManager.InkManager.CopySelectedToClipboard();

            foreach (InkStroke inkStroke in inkFileManager.InkManager.GetStrokes())
                inkStroke.Selected = false;

            inkFileManager.RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnCutAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;
            inkFileManager.InkManager.CopySelectedToClipboard();
            inkFileManager.InkManager.DeleteSelected();
            inkFileManager.RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnPasteAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;
            inkFileManager.InkManager.PasteFromClipboard(new Point());
            inkFileManager.RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnDeleteAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;
            inkFileManager.InkManager.DeleteSelected();
            inkFileManager.RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnPenSizeComboBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            if (penSizeComboBox.SelectedItem == null)
                return;

            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;

            double penSize = (double)penSizeComboBox.SelectedItem;
            Size size = new Size(penSize, penSize);

            if (!inkFileManager.IsAnythingSelected)
            {
                inkFileManager.InkDrawingAttributes.Size = size;
                inkFileManager.UpdateAttributes();
            }
            else
            {
                foreach (InkStroke inkStroke in inkFileManager.InkManager.GetStrokes())
                    if (inkStroke.Selected)
                    {
                        InkDrawingAttributes drawingAttrs = inkStroke.DrawingAttributes;
                        drawingAttrs.Size = size;
                        inkStroke.DrawingAttributes = drawingAttrs;
                    }
                inkFileManager.RenderAll();
            }
        }

        void OnColorComboBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            if (colorComboBox.SelectedItem == null)
                return;

            InkFileManager inkFileManager = (InkFileManager)flipView.SelectedItem;

            Color color = (Color)colorComboBox.SelectedItem;

            if (!inkFileManager.IsAnythingSelected)
            {
                inkFileManager.InkDrawingAttributes.Color = color;
                inkFileManager.UpdateAttributes();
            }
            else
            {
                foreach (InkStroke inkStroke in inkFileManager.InkManager.GetStrokes())
                    if (inkStroke.Selected)
                    {
                        InkDrawingAttributes drawingAttrs = inkStroke.DrawingAttributes;
                        drawingAttrs.Color = color;
                        inkStroke.DrawingAttributes = drawingAttrs;
                    }
                inkFileManager.RenderAll();
            }
        }
    }
}
