using System;
using Windows.ApplicationModel;
using Windows.ApplicationModel.DataTransfer;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.ApplicationSettings;
using Windows.UI.Popups;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace FingerPaint
{
    public sealed partial class MainPage : Page
    {
        AppSettings appSettings = new AppSettings();
        double imageScale = 1;
        Point imageOffset = new Point();

        public MainPage()
        {
            this.InitializeComponent();

            SizeChanged += OnMainPageSizeChanged;
            Loaded += OnMainPageLoaded;
            Application.Current.Suspending += OnApplicationSuspending;

            // Install a handler for the Settings pane
            SettingsPane settingsPane = SettingsPane.GetForCurrentView();
            settingsPane.CommandsRequested += OnSettingsPaneCommandsRequested;

            // Call a method in MainPage.Share.cs
            InitializeSharing();

            // Create a PrintDocument derivative for handling printing
            new BitmapPrintDocument(() => { return bitmap; });
        }

        void OnSettingsPaneCommandsRequested(SettingsPane sender, 
                                             SettingsPaneCommandsRequestedEventArgs args)
        {
            SettingsCommand aboutCommand = new SettingsCommand(0, "About", OnAboutInvoked);
            args.Request.ApplicationCommands.Add(aboutCommand);
        }

        void OnAboutInvoked(IUICommand command)
        {
            AboutBox aboutBox = new AboutBox();
            aboutBox.Height = this.ActualHeight;

            Popup popup = new Popup
            {
                IsLightDismissEnabled = true,
                Child = aboutBox,
                IsOpen = true,
                HorizontalOffset = this.ActualWidth - aboutBox.Width
            };
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            VisualStateManager.GoToState(this, ApplicationView.Value.ToString(), true);

            if (bitmap != null)
            {
                CalculateImageScaleAndOffset();
            }
        }

        void CalculateImageScaleAndOffset()
        {
            imageScale = Math.Min(this.ActualWidth / bitmap.PixelWidth,
                                  this.ActualHeight / bitmap.PixelHeight);
            imageOffset = new Point((this.ActualWidth - imageScale * bitmap.PixelWidth) / 2,
                                    (this.ActualHeight - imageScale * bitmap.PixelHeight) / 2);
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            try
            {
                StorageFolder localFolder = ApplicationData.Current.LocalFolder;
                StorageFile storageFile = await localFolder.GetFileAsync("FingerPaint.png");
                await LoadBitmapFromFile(storageFile);
            }
            catch
            {
                // Ignore any errors
            }

            if (bitmap == null)
                await CreateNewBitmapAndPixelArray();
        }

        async void OnApplicationSuspending(object sender, SuspendingEventArgs args)
        {
            // Save application settings
            appSettings.Save();

            // Save current bitmap
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();

            try
            {
                StorageFolder localFolder = ApplicationData.Current.LocalFolder;
                StorageFile storageFile = await localFolder.CreateFileAsync("FingerPaint.png",
                                                        CreationCollisionOption.ReplaceExisting);
                await SaveBitmapToFile(storageFile);
            }
            catch
            {
                // Ignore any errors
            }

            deferral.Complete();
        }

        void OnColorAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            DisplayDialog(sender, new ColorSettingDialog());
        }

        void OnThicknessAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            DisplayDialog(sender, new ThicknessSettingDialog());
        }

        void DisplayDialog(object sender, FrameworkElement dialog)
        {
            dialog.DataContext = appSettings;

            Popup popup = new Popup
            {
                Child = dialog,
                IsLightDismissEnabled = true
            };

            dialog.SizeChanged += (dialogSender, dialogArgs) =>
            {
                // Get Button location relative to screen
                Button btn = sender as Button;
                Point pt = btn.TransformToVisual(null).TransformPoint(
                                                            new Point(btn.ActualWidth / 2,
                                                                      btn.ActualHeight / 2));

                popup.HorizontalOffset = Math.Max(24, pt.X - dialog.ActualWidth / 2);

                if (popup.HorizontalOffset + dialog.ActualWidth > this.ActualWidth)
                    popup.HorizontalOffset = this.ActualWidth - dialog.ActualWidth;

                popup.HorizontalOffset = Math.Max(0, popup.HorizontalOffset);

                popup.VerticalOffset = this.ActualHeight - dialog.ActualHeight
                                                         - this.BottomAppBar.ActualHeight - 24;
            };

            popup.Closed += (popupSender, popupArgs) =>
            {
                this.BottomAppBar.IsOpen = false;
            };

            popup.IsOpen = true;
        }
    }
}
