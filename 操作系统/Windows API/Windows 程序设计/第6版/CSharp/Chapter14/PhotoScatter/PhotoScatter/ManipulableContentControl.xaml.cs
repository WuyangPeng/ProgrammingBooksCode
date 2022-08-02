using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace PhotoScatter
{
    public sealed partial class ManipulableContentControl : ContentControl
    {
        static int zIndex;
        ManipulationManager manipulationManager;

        public ManipulableContentControl(CompositeTransform initialTransform)
        {
            this.InitializeComponent();

            // Create the ManipulationManager and set MatrixTransform from it
            manipulationManager = new ManipulationManager(initialTransform);
            matrixXform.Matrix = manipulationManager.Matrix;

            this.ManipulationMode = ManipulationModes.All &
                                   ~ManipulationModes.TranslateRailsX &
                                   ~ManipulationModes.TranslateRailsY;
        }

        protected override void OnManipulationStarting(ManipulationStartingRoutedEventArgs args)
        {
            Canvas.SetZIndex(this, zIndex += 1);
            base.OnManipulationStarting(args);
        }

        protected override void OnManipulationDelta(ManipulationDeltaRoutedEventArgs args)
        {
            manipulationManager.AccumulateDelta(args.Position, args.Delta);
            matrixXform.Matrix = manipulationManager.Matrix;
            base.OnManipulationDelta(args);
        }
    }
}
