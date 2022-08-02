using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace DisplayHighSchoolStudents
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            SizeChanged += OnPageSizeChanged;
        }

        void OnPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            VisualStateManager.GoToState(this, ApplicationView.Value.ToString(), true);
        }

        void OnGridViewItemClick(object sender, ItemClickEventArgs args)
        {
            this.Frame.Navigate(typeof(StudentPage), args.ClickedItem);
        }
    }
}
