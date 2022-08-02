using Windows.Foundation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace SingleFingerRotate
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            image.ManipulationMode = ManipulationModes.All &
                                    ~ManipulationModes.TranslateRailsX &
                                    ~ManipulationModes.TranslateRailsY;
        }

        protected override void OnManipulationStarting(ManipulationStartingRoutedEventArgs args)
        {
            args.Pivot = new ManipulationPivot(new Point(image.ActualWidth / 2, 
                                                         image.ActualHeight / 2),
                                               50);
            base.OnManipulationStarting(args);
        }

        protected override void OnManipulationDelta(ManipulationDeltaRoutedEventArgs args)
        {
            // Make this the entire transform to date
            matrixXform.Matrix = xformGroup.Value;

            // Use that to transform the Position property
            Point center = matrixXform.TransformPoint(args.Position);

            // That becomes the center of the new incremental transform
            compositeXform.CenterX = center.X;
            compositeXform.CenterY = center.Y;

            // Set the other properties
            compositeXform.TranslateX = args.Delta.Translation.X;
            compositeXform.TranslateY = args.Delta.Translation.Y;
            compositeXform.ScaleX = args.Delta.Scale;
            compositeXform.ScaleY = args.Delta.Scale;
            compositeXform.Rotation = args.Delta.Rotation;

            base.OnManipulationDelta(args);
        }
    }
}
