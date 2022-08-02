using System;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace ClockRack
{
    public sealed partial class MainPage : Page
    {
        TimeZoneManager timeZoneManager = new TimeZoneManager();
        IPropertySet appSettings = ApplicationData.Current.LocalSettings.Values;

        public MainPage()
        {
            this.InitializeComponent();

            // Load application settings for clocks
            int index = 0;

            while (appSettings.ContainsKey(index.ToString() + "Location"))
            {
                string preface = index.ToString();

                TimeZoneClock clock = new TimeZoneClock
                {
                    DataContext = new TimeZoneClockViewModel
                    {
                        Location = appSettings[preface + "Location"] as string,
                        TimeZoneKey = appSettings[preface + "TimeZoneKey"] as string,
                        ForegroundName = appSettings[preface + "Foreground"] as string,
                        BackgroundName = appSettings[preface + "Background"] as string 
                    },
                };
                uniformGrid.Children.Add(clock);
                index += 1;
            }

            // If there are no settings, make a default Clock
            if (uniformGrid.Children.Count == 0)
            {
                TimeZoneClock clock = new TimeZoneClock
                {
                    DataContext = new TimeZoneClockViewModel()
                };
                uniformGrid.Children.Add(clock);
            }

            // Set the Suspending handler
            Application.Current.Suspending += OnApplicationSuspending;

            // Start the Rendering event
            CompositionTarget.Rendering += OnCompositionTargetRendering;
        }

        void OnApplicationSuspending(object sender, SuspendingEventArgs args)
        {
            appSettings.Clear();

            for (int index = 0; index < uniformGrid.Children.Count; index++)
            {
                TimeZoneClock timeZoneClock = uniformGrid.Children[index] as TimeZoneClock;
                TimeZoneClockViewModel viewModel =
                        timeZoneClock.DataContext as TimeZoneClockViewModel;
                string preface = index.ToString();

                appSettings[preface + "Location"] = viewModel.Location;
                appSettings[preface + "TimeZoneKey"] = viewModel.TimeZoneKey;
                appSettings[preface + "Foreground"] = viewModel.ForegroundName;
                appSettings[preface + "Background"] = viewModel.BackgroundName;
            }
        }

        void OnCompositionTargetRendering(object sender, object args)
        {
            // Get the time once
            DateTime utc = DateTime.UtcNow;

            foreach (UIElement child in uniformGrid.Children)
            {
                TimeZoneClockViewModel viewModel = 
                        (child as FrameworkElement).DataContext as TimeZoneClockViewModel;
                string timeZoneKey = viewModel.TimeZoneKey;

                // Set the local time from the TimeZoneManager
                viewModel.DateTime = timeZoneManager.GetLocalTime(timeZoneKey, utc);
            }
        }

        async protected override void OnRightTapped(RightTappedRoutedEventArgs args)
        {
            // Find the underlying TimeZoneClock
            FrameworkElement element = args.OriginalSource as FrameworkElement;

            while (element != null)
            {
                if (element is TimeZoneClock)
                    break;

                element = element.Parent as FrameworkElement;
            }

            if (element == null)
                return;

            // Create a PopupMenu 
            PopupMenu popupMenu = new PopupMenu();
            popupMenu.Commands.Add(new UICommand("Add", OnAddMenuItem, element));
            popupMenu.Commands.Add(new UICommand("Edit...", OnEditMenuItem, element));

            if (uniformGrid.Children.Count > 1)
                popupMenu.Commands.Add(new UICommand("Delete", OnDeleteMenuItem, element));

            args.Handled = true;
            base.OnRightTapped(args);

            // Display the menu
            await popupMenu.ShowAsync(args.GetPosition(this));
        }

        void OnAddMenuItem(IUICommand command)
        {
            // Create new TimeZoneClock
            TimeZoneClock timeZoneClock = new TimeZoneClock
            {
                DataContext = new TimeZoneClockViewModel()
            };

            // Insert after the tapped clock
            TimeZoneClock clickedClock = command.Id as TimeZoneClock;
            int index = uniformGrid.Children.IndexOf(clickedClock);
            uniformGrid.Children.Insert(index + 1, timeZoneClock);
        }

        void OnEditMenuItem(IUICommand command)
        {
            TimeZoneClock timeZoneClock = command.Id as TimeZoneClock;
            SettingsDialog settingsDialog = new SettingsDialog(timeZoneManager);
            settingsDialog.DataContext = timeZoneClock.DataContext;

            // Create Popup with SettingsDialog child
            Popup popup = new Popup
            {
                Child = settingsDialog,
                IsLightDismissEnabled = true
            };

            settingsDialog.SizeChanged += (sender, args) =>
                {
                    // Get clock center
                    Point position = new Point(timeZoneClock.ActualWidth / 2,
                                               timeZoneClock.ActualHeight / 2);

                    // Convert to Page coordinates
                    position = timeZoneClock.TransformToVisual(this).TransformPoint(position);

                    // Position popup so lower-left or lower-right corner 
                    //      aligns with center of edited clock
                    if (position.X > this.ActualWidth / 2)
                        position.X -= settingsDialog.ActualWidth;

                    position.Y -= settingsDialog.ActualHeight;

                    // Adjust for size of page
                    if (position.X + settingsDialog.ActualWidth > this.ActualWidth)
                        position.X = this.ActualWidth - settingsDialog.ActualWidth;

                    if (position.X < 0)
                        position.X = 0;

                    if (position.Y < 0)
                        position.Y = 0;

                    // Set the Popup position
                    popup.HorizontalOffset = position.X;
                    popup.VerticalOffset = position.Y;
                };

            popup.IsOpen = true;
        }

        async void OnDeleteMenuItem(IUICommand command)
        {
            TimeZoneClock timeZoneClock = command.Id as TimeZoneClock;
            TimeZoneClockViewModel viewModel = timeZoneClock.DataContext as TimeZoneClockViewModel;

            MessageDialog msgdlg = new MessageDialog("Delete clock from collection?", 
                                                     viewModel.Location);
            msgdlg.Commands.Add(new UICommand("OK"));
            msgdlg.Commands.Add(new UICommand("Cancel"));
            msgdlg.DefaultCommandIndex = 0;
            msgdlg.CancelCommandIndex = 1;

            IUICommand msgDlgCommand = await msgdlg.ShowAsync();

            if (msgDlgCommand.Label == "OK")
                uniformGrid.Children.Remove(command.Id as TimeZoneClock);
        }
    }
}
