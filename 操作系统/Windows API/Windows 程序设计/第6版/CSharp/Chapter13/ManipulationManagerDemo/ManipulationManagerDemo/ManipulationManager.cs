using Windows.Foundation;
using Windows.UI.Input;
using Windows.UI.Xaml.Media;

namespace ManipulationManagerDemo
{
    public class ManipulationManager
    {
        TransformGroup xformGroup;
        MatrixTransform matrixXform;
        CompositeTransform compositeXform;

        public ManipulationManager()
        {
            xformGroup = new TransformGroup();
            matrixXform = new MatrixTransform();
            xformGroup.Children.Add(matrixXform);
            compositeXform = new CompositeTransform();
            xformGroup.Children.Add(compositeXform);
            this.Matrix = Matrix.Identity;
        }

        public Matrix Matrix { private set; get; }

        public void AccumulateDelta(Point position, ManipulationDelta delta)
        {
            matrixXform.Matrix = xformGroup.Value;
            Point center = matrixXform.TransformPoint(position);
            compositeXform.CenterX = center.X;
            compositeXform.CenterY = center.Y;
            compositeXform.TranslateX = delta.Translation.X;
            compositeXform.TranslateY = delta.Translation.Y;
            compositeXform.ScaleX = delta.Scale;
            compositeXform.ScaleY = delta.Scale;
            compositeXform.Rotation = delta.Rotation;
            this.Matrix = xformGroup.Value;
        }
    }
}
