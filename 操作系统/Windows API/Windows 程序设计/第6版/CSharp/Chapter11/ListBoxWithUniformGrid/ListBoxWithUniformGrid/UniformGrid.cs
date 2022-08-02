using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace ListBoxWithUniformGrid
{
    public class UniformGrid : Panel
    {
        // Set by MeasureOverride, used in ArrangeOverride
        protected int rows, cols;

        static UniformGrid()
        {
            RowsProperty = DependencyProperty.Register("Rows", 
                typeof(int?), 
                typeof(UniformGrid), 
                new PropertyMetadata(null, OnPropertyChanged));

            ColumnsProperty = DependencyProperty.Register("Columns", 
                typeof(int?), 
                typeof(UniformGrid), 
                new PropertyMetadata(null, OnPropertyChanged));

            OrientationProperty = DependencyProperty.Register("Orientation",
                typeof(Orientation),
                typeof(UniformGrid),
                new PropertyMetadata(Orientation.Horizontal, OnPropertyChanged));
        }

        public static DependencyProperty RowsProperty { private set; get; }

        public static DependencyProperty ColumnsProperty { private set; get; }

        public static DependencyProperty OrientationProperty { private set; get; }

        public int? Rows
        {
            set { SetValue(RowsProperty, value); }
            get { return (int?)GetValue(RowsProperty); }
        }

        public int? Columns
        {
            set { SetValue(ColumnsProperty, value); }
            get { return (int?)GetValue(ColumnsProperty); }
        }

        public Orientation Orientation
        {
            set { SetValue(OrientationProperty, value); }
            get { return (Orientation)GetValue(OrientationProperty); }
        }

        protected override Size MeasureOverride(Size availableSize)
        {
            // Only bother if children actually exist
            if (this.Children.Count == 0)
                return new Size();

            // Throw exceptions if the properties aren't OK
            if (this.Rows.HasValue && this.Rows.Value < 1)
                throw new ArgumentOutOfRangeException("UniformGrid Rows must be greater than zero");

            if (this.Columns.HasValue && this.Columns.Value < 1)
                throw new ArgumentOutOfRangeException("UniformGrid Columns must be greater than zero");

            // Determine the actual number of rows and columns
            // ----------------------------------------
            // This option is discouraged
            if (this.Rows.HasValue && this.Columns.HasValue)
            {
                rows = this.Rows.Value;
                cols = this.Columns.Value;
            }
            // These two options often appear with values of 1
            else if (this.Rows.HasValue)
            {
                rows = this.Rows.Value;
                cols = (int)Math.Ceiling((double)this.Children.Count / rows);
            }
            else if (this.Columns.HasValue)
            {
                cols = this.Columns.Value;
                rows = (int)Math.Ceiling((double)this.Children.Count / cols);
            }
            // No values yet if both Rows and Columns are null, but
            //      check for infinite availableSize
            else if (Double.IsInfinity(availableSize.Width) &&
                     Double.IsInfinity(availableSize.Height))
            {
                throw new NotSupportedException("Completely unconstrained UniformGrid " +
                                                "requires non-null Rows or Columns property");
            }

            // Determine the maximum size of all children
            // ------------------------------------------
            Size maximumSize = new Size();
            Size infiniteSize = new Size(Double.PositiveInfinity, 
                                         Double.PositiveInfinity);

            // Find the maximum size of all children
            foreach (UIElement child in this.Children)
            {
                child.Measure(infiniteSize);
                Size childSize = child.DesiredSize;
                maximumSize.Width = Math.Max(maximumSize.Width, childSize.Width);
                maximumSize.Height = Math.Max(maximumSize.Height, childSize.Height);
            }

            // Find rows and cols if Rows and Colunms are both null
            if (!this.Rows.HasValue && !this.Columns.HasValue)
            {
                if (!Double.IsInfinity(availableSize.Height))
                {
                    rows = (int)Math.Max(1, availableSize.Height / maximumSize.Height);
                    cols = (int)Math.Ceiling((double)this.Children.Count / rows);
                }
                else if (!Double.IsInfinity(availableSize.Width))
                {
                    cols = (int)Math.Max(1, availableSize.Width / maximumSize.Width);
                    rows = (int)Math.Ceiling((double)this.Children.Count / cols);
                }
                // Neither dimension is infinite -- the hard one
                else
                {
                    double aspectRatio = maximumSize.Width / maximumSize.Height;
                    double bestHeight = 0;
                    double bestWidth = 0;

                    for (int tryRows = 1; tryRows < this.Children.Count; tryRows++)
                    {
                        int tryCols = (int)Math.Ceiling((double)this.Children.Count / tryRows);
                        double childHeight = availableSize.Height / tryRows;
                        double childWidth = availableSize.Width / tryCols;

                        // Adjust for aspect ratio
                        if (childWidth > aspectRatio * childHeight)
                            childWidth = aspectRatio * childHeight;
                        else
                            childHeight = childWidth / aspectRatio;

                        // Check if it's larger than other trials
                        if (childHeight > bestHeight)
                        {
                            bestHeight = childHeight;
                            bestWidth = childWidth;
                            rows = tryRows;
                            cols = tryCols;
                        }
                    }
                }
            }

            // Return desired size
            return new Size(cols * maximumSize.Width, rows * maximumSize.Height);
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            int index = 0;
            double cellWidth = finalSize.Width / cols;
            double cellHeight = finalSize.Height / rows;

            if (this.Orientation == Orientation.Horizontal)
            {
                for (int row = 0; row < rows; row++)
                {
                    double y = row * cellHeight;

                    for (int col = 0; col < cols; col++)
                    {
                        double x = col * cellWidth;
                        this.Children[index].Arrange(new Rect(x, y, cellWidth, cellHeight));
                        index++;
                    }
                }
            }
            else
            {
                for (int col = 0; col < cols; col++)
                {
                    double x = col * cellWidth;

                    for (int row = 0; row < rows; row++)
                    {
                        double y = row * cellHeight;
                        this.Children[index].Arrange(new Rect(x, y, cellWidth, cellHeight));
                        index++;
                    }
                }
           }
            
            return base.ArrangeOverride(finalSize);
        }

        static void OnPropertyChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            if (args.Property == UniformGrid.OrientationProperty)
            {
                (obj as UniformGrid).InvalidateArrange();
            }
            else
            {
                (obj as UniformGrid).InvalidateMeasure();
            }
        }
    }
}
