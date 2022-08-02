using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace DigitalClock
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            DispatcherTimer timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += OnTimerTick;
            timer.Start();
        }

        void OnTimerTick(object sender, object e)
        {
            txtblk.Text = DateTime.Now.ToString("h:mm:ss tt");
        }
    }
}
