using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.System;
using Windows.UI.Core;
using Windows.UI.Input;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Application template is documented at http://go.microsoft.com/fwlink/?LinkId=234227

namespace ApplicationStateSave
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    sealed partial class App : Application
    {
        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used when the application is launched to open a specific file, to display
        /// search results, and so forth.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs args)
        {
            Frame rootFrame = Window.Current.Content as Frame;

            // Do not repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                // Create a Frame to act as the navigation context and navigate to the first page
                rootFrame = new Frame();

                if (args.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: Load state from previously suspended application

                    // Code added for ApplicationStateSave project
                    ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

                    if (appData.Values.ContainsKey("NavigationState"))
                        rootFrame.SetNavigationState(appData.Values["NavigationState"] as string);
                    // End of code added for ApplicationStateSave project
                }

                // Place the frame in the current Window
                Window.Current.Content = rootFrame;
            }

            if (rootFrame.Content == null)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                if (!rootFrame.Navigate(typeof(MainPage), args.Arguments))
                {
                    throw new Exception("Failed to create initial page");
                }
            }
            // Ensure the current window is active
            Window.Current.Activate();

            // Code added for ApplicationStateSave project
            Window.Current.CoreWindow.Dispatcher.AcceleratorKeyActivated += OnAcceleratorKeyActivated;
            Window.Current.CoreWindow.PointerPressed += OnPointerPressed;
            // End of code added for ApplicationStateSave project
        }

        void OnAcceleratorKeyActivated(CoreDispatcher sender, AcceleratorKeyEventArgs args)
        {
            if ((args.EventType == CoreAcceleratorKeyEventType.SystemKeyDown ||
                 args.EventType == CoreAcceleratorKeyEventType.KeyDown) &&
                (args.VirtualKey == VirtualKey.Left || 
                args.VirtualKey == VirtualKey.Right ||
                (int)args.VirtualKey == 166 || 
                (int)args.VirtualKey == 167))
            {
                CoreWindow window = Window.Current.CoreWindow;
                CoreVirtualKeyStates down = CoreVirtualKeyStates.Down;

                // Ignore key combinations where Shift or Ctrl is down
                if ((window.GetKeyState(VirtualKey.Shift) & down) == down ||
                    (window.GetKeyState(VirtualKey.Control) & down) == down)
                {
                    return;
                }

                // Get alt key state
                bool alt = (window.GetKeyState(VirtualKey.Menu) & down) == down;

                // Go back for Alt-Left key or browser left key
                if (args.VirtualKey == VirtualKey.Left && alt ||
                    (int)args.VirtualKey == 166 && !alt)
                {
                    GoBack();
                    args.Handled = true;
                }

                // Go forward for Alt-Right key or browser right key
                if (args.VirtualKey == VirtualKey.Right && alt ||
                    (int)args.VirtualKey == 167 && !alt)
                {
                    GoForward();
                    args.Handled = true;
                }
            }
        }

        void OnPointerPressed(CoreWindow sender, PointerEventArgs args)
        {
            PointerPointProperties props = args.CurrentPoint.Properties;

            if (!props.IsLeftButtonPressed &&
                !props.IsMiddleButtonPressed &&
                !props.IsRightButtonPressed &&
                props.IsXButton1Pressed != props.IsXButton2Pressed)
            {
                if (props.IsXButton1Pressed)
                    GoBack();
                else
                    GoForward();

                args.Handled = true;
            }
        }

        void GoBack()
        {
            Frame frame = Window.Current.Content as Frame;

            if (frame != null && frame.CanGoBack)
                frame.GoBack();
        }

        void GoForward()
        {
            Frame frame = Window.Current.Content as Frame;

            if (frame != null && frame.CanGoForward)
                frame.GoForward();
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity

            // Code added for ApplicationStateSave project
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;
            appData.Values["NavigationState"] = (Window.Current.Content as Frame).GetNavigationState();
            // End of code added for ApplicationStateSave project

            deferral.Complete();
        }
    }
}
