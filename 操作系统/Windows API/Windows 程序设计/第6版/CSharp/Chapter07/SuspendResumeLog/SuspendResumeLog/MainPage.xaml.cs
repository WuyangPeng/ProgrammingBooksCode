using System;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace SuspendResumeLog
{
    public sealed partial class MainPage : Page
    {
        StorageFile logfile;

        public MainPage()
        {
            this.InitializeComponent();

            Loaded += OnLoaded;
            Application.Current.Suspending += OnAppSuspending;
            Application.Current.Resuming += OnAppResuming;
        }

        async void OnLoaded(object sender, RoutedEventArgs args)
        {
            // Create or obtain the log file
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;
            logfile = await localFolder.CreateFileAsync("logfile.txt", 
                                                CreationCollisionOption.OpenIfExists);

            // Load the file and display it
            txtbox.Text = await FileIO.ReadTextAsync(logfile);

            // Log the launch
            txtbox.Text += String.Format("Launching at {0}\r\n", DateTime.Now.ToString());
            await FileIO.WriteTextAsync(logfile, txtbox.Text);
        }

        async void OnAppSuspending(object sender, SuspendingEventArgs args)
        {
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();

            // Log the suspension
            txtbox.Text += String.Format("Suspending at {0}\r\n", DateTime.Now.ToString());
            await FileIO.WriteTextAsync(logfile, txtbox.Text);

            deferral.Complete();
        }

        async void OnAppResuming(object sender, object args)
        {
            // Log the resumption
            txtbox.Text += String.Format("Resuming at {0}\r\n", DateTime.Now.ToString());
            await FileIO.WriteTextAsync(logfile, txtbox.Text);
        }
    }
}
