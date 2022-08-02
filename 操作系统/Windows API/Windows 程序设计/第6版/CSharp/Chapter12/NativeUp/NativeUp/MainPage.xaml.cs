using Windows.Graphics.Display;
using Windows.UI.Xaml.Controls;

namespace NativeUp
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            SetRotation();
            DisplayProperties.OrientationChanged += OnOrientationChanged;
        }

        void OnOrientationChanged(object sender)
        {
            SetRotation();
        }

        void SetRotation()
        {
            rotate.Angle = 90 * (Log2(DisplayProperties.CurrentOrientation) -
                                 Log2(DisplayProperties.NativeOrientation));
        }

        int Log2(DisplayOrientations orientation)
        {
            int value = (int)orientation;
            int log = 0;

            while (value > 0 && (value & 1) == 0)
            {
                value >>= 1;
                log += 1;
            }
            return log;
        }
    }
}
