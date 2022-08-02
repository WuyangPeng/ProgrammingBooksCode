using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace DisplayHighSchoolStudents
{
    public sealed partial class StudentPage : Page
    {
        public StudentPage()
        {
            this.InitializeComponent();
            SizeChanged += OnPageSizeChanged;
        }

        void OnPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            VisualStateManager.GoToState(this, ApplicationView.Value.ToString(), true);
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            this.DataContext = args.Parameter;
            base.OnNavigatedTo(args);
        }

        void OnBackButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.GoBack();
        }
    }
}
