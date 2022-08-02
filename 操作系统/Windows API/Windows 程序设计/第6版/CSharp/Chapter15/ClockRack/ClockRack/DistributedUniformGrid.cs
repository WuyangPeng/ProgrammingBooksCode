using System;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;
using Petzold.ProgrammingWindows6.Chapter11;

namespace ClockRack
{
    public class DistributedUniformGrid : UniformGrid
    {
        protected override Size ArrangeOverride(Size finalSize)
        {
            int index = 0;
            double cellWidth = finalSize.Width / cols;
            double cellHeight = finalSize.Height / rows;
            int displayed = 0;

            if (this.Orientation == Orientation.Vertical)
            {
                for (int row = 0; row < rows; row++)
                {
                    double y = row * cellHeight;
                    int accumDisplay = (int)Math.Ceiling((row + 1.0) * this.Children.Count / rows);
                    int display = accumDisplay - displayed;
                    cellWidth = Math.Round(finalSize.Width / display);
                    double x = 0;

                    for (int col = 0; col < display; col++)
                    {
                        if (index < this.Children.Count)
                            this.Children[index].Arrange(new Rect(x, y, cellWidth, cellHeight));

                        x += cellWidth;
                        index++;
                    }
                    displayed += display;
                }
            }
            else
            {
                for (int col = 0; col < cols; col++)
                {
                    double x = col * cellWidth;
                    int accumDisplay = (int)Math.Ceiling((col + 1.0) * this.Children.Count / cols);
                    int display = accumDisplay - displayed;
                    cellHeight = Math.Round(finalSize.Height / display);
                    double y = 0;

                    for (int row = 0; row < display; row++)
                    {
                        if (index < this.Children.Count)
                            this.Children[index].Arrange(new Rect(x, y, cellWidth, cellHeight));

                        y += cellHeight;
                        index++;
                    }
                    displayed += display;
                }
            }
            return finalSize;
        }
    }
}
