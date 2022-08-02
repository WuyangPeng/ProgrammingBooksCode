using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace ManipulationManagerDemo
{
    public sealed partial class MainPage : Page
    {
        ManipulationManager manipulationManager = new ManipulationManager();

        public MainPage()
        {
            this.InitializeComponent();

            image.ManipulationMode = ManipulationModes.All &
                                    ~ManipulationModes.TranslateRailsX &
                                    ~ManipulationModes.TranslateRailsY;
        }

        protected override void OnManipulationDelta(ManipulationDeltaRoutedEventArgs args)
        {
            manipulationManager.AccumulateDelta(args.Position, args.Delta);
            matrixXform.Matrix = manipulationManager.Matrix;
            base.OnManipulationDelta(args);
        }
    }
}
