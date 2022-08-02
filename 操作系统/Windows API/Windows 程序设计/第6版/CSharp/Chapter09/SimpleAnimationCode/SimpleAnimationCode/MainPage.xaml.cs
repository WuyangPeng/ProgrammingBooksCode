using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Animation;

namespace SimpleAnimationCode
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnButtonClick(object sender, RoutedEventArgs args)
        {
            DoubleAnimation anima = new DoubleAnimation
            {
                EnableDependentAnimation = true,
                To = 96,
                Duration = new Duration(new TimeSpan(0, 0, 1)),
                AutoReverse = true,
                RepeatBehavior = new RepeatBehavior(3)
            };
            Storyboard.SetTarget(anima, sender as Button);
            Storyboard.SetTargetProperty(anima, "FontSize");

            Storyboard storyboard = new Storyboard();
            storyboard.Children.Add(anima);
            storyboard.Begin();
        }
    }
}
