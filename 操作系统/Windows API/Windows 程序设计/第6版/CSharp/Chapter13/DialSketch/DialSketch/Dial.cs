using System;
using Windows.Foundation;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;

namespace DialSketch
{
    public class Dial : RangeBase
    {
        public Dial()
        {
            ManipulationMode = ManipulationModes.Rotate;
        }

        protected override void OnManipulationStarting(ManipulationStartingRoutedEventArgs args)
        {
            args.Pivot = new ManipulationPivot(new Point(this.ActualWidth / 2, 
                                                         this.ActualHeight / 2), 
                                               48);
            base.OnManipulationStarting(args);
        }

        protected override void OnManipulationDelta(ManipulationDeltaRoutedEventArgs args)
        {
            this.Value = Math.Max(this.Minimum, 
                         Math.Min(this.Maximum, this.Value + args.Delta.Rotation));

            base.OnManipulationDelta(args);
        }
    }
}
