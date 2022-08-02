using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace XamlCruncher
{
    public sealed partial class RulerContainer : UserControl
    {
        const double RULER_WIDTH = 12;

        static RulerContainer()
        {
            ChildProperty =
                DependencyProperty.Register("Child",
                    typeof(UIElement), typeof(RulerContainer),
                    new PropertyMetadata(null, OnChildChanged));

            ShowRulerProperty =
                DependencyProperty.Register("ShowRuler",
                    typeof(bool), typeof(RulerContainer),
                    new PropertyMetadata(false, OnShowRulerChanged));

            ShowGridLinesProperty =
                DependencyProperty.Register("ShowGridLines",
                    typeof(bool), typeof(RulerContainer),
                    new PropertyMetadata(false, OnShowGridLinesChanged));
        }

        public static DependencyProperty ChildProperty { private set; get; }
        public static DependencyProperty ShowRulerProperty { private set; get; }
        public static DependencyProperty ShowGridLinesProperty { private set; get; }

        public RulerContainer()
        {
            this.InitializeComponent();
        }

        public UIElement Child
        {
            set { SetValue(ChildProperty, value); }
            get { return (UIElement)GetValue(ChildProperty); }
        }

        public bool ShowRuler
        {
            set { SetValue(ShowRulerProperty, value); }
            get { return (bool)GetValue(ShowRulerProperty); }
        }

        public bool ShowGridLines
        {
            set { SetValue(ShowGridLinesProperty, value); }
            get { return (bool)GetValue(ShowGridLinesProperty); }
        }

        // Property changed handlers
        static void OnChildChanged(DependencyObject obj,
                                   DependencyPropertyChangedEventArgs args)
        {
            (obj as RulerContainer).border.Child = (UIElement)args.NewValue;
        }

        static void OnShowRulerChanged(DependencyObject obj,
                                       DependencyPropertyChangedEventArgs args)
        {
            (obj as RulerContainer).RedrawRuler();
        }

        static void OnShowGridLinesChanged(DependencyObject obj,
                                           DependencyPropertyChangedEventArgs args)
        {
            (obj as RulerContainer).RedrawGridLines();
        }

        void OnGridSizeChanged(object sender, SizeChangedEventArgs args)
        {
            RedrawRuler();
            RedrawGridLines();
        }

        void RedrawGridLines()
        {
            gridLinesGrid.Children.Clear();

            if (!this.ShowGridLines)
                return;

            // Vertical grid lines every 1/4"
            for (double x = 24; x < gridLinesGrid.ActualWidth; x += 24)
            {
                Line line = new Line
                {
                    X1 = x,
                    Y1 = 0,
                    X2 = x,
                    Y2 = gridLinesGrid.ActualHeight,
                    Stroke = this.Foreground,
                    StrokeThickness = x % 96 == 0 ? 1 : 0.5
                };
                gridLinesGrid.Children.Add(line);
            }

            // Horizontal grid lines every 1/4"
            for (double y = 24; y < gridLinesGrid.ActualHeight; y += 24)
            {
                Line line = new Line
                {
                    X1 = 0,
                    Y1 = y,
                    X2 = gridLinesGrid.ActualWidth,
                    Y2 = y,
                    Stroke = this.Foreground,
                    StrokeThickness = y % 96 == 0 ? 1 : 0.5
                };
                gridLinesGrid.Children.Add(line);
            }
        }

        void RedrawRuler()
        {
            rulerCanvas.Children.Clear();

            if (!this.ShowRuler)
            {
                innerGrid.Margin = new Thickness();
                return;
            }

            innerGrid.Margin = new Thickness(RULER_WIDTH, RULER_WIDTH, 0, 0);

            // Ruler across the top
            for (double x = 0; x < gridLinesGrid.ActualWidth - RULER_WIDTH; x += 12)
            {
                // Numbers every inch
                if (x > 0 && x % 96 == 0)
                {
                    TextBlock txtblk = new TextBlock
                    {
                        Text = (x / 96).ToString("F0"),
                        FontSize = RULER_WIDTH - 2
                    };

                    txtblk.Measure(new Size());
                    Canvas.SetLeft(txtblk, RULER_WIDTH + x - txtblk.ActualWidth / 2);
                    Canvas.SetTop(txtblk, 0);
                    rulerCanvas.Children.Add(txtblk);
                }
                // Tick marks every 1/8"
                else
                {
                    Line line = new Line
                    {
                        X1 = RULER_WIDTH + x,
                        Y1 = x % 48 == 0 ? 2 : 4,
                        X2 = RULER_WIDTH + x,
                        Y2 = x % 48 == 0 ? RULER_WIDTH - 2 : RULER_WIDTH - 4,
                        Stroke = this.Foreground,
                        StrokeThickness = 1
                    };
                    rulerCanvas.Children.Add(line);
                }
            }

            // Heavy line underneath the tick marks
            Line topLine = new Line
            {
                X1 = RULER_WIDTH - 1,
                Y1 = RULER_WIDTH - 1,
                X2 = rulerCanvas.ActualWidth,
                Y2 = RULER_WIDTH - 1,
                Stroke = this.Foreground,
                StrokeThickness = 2
            };
            rulerCanvas.Children.Add(topLine);

            // Ruler down the left side
            for (double y = 0; y < gridLinesGrid.ActualHeight - RULER_WIDTH; y += 12)
            {
                // Numbers every inch
                if (y > 0 && y % 96 == 0)
                {
                    TextBlock txtblk = new TextBlock
                    {
                        Text = (y / 96).ToString("F0"),
                        FontSize = RULER_WIDTH - 2,
                    };

                    txtblk.Measure(new Size());
                    Canvas.SetLeft(txtblk, 2);
                    Canvas.SetTop(txtblk, RULER_WIDTH + y - txtblk.ActualHeight / 2);
                    rulerCanvas.Children.Add(txtblk);
                }
                // Tick marks every 1/8"
                else
                {
                    Line line = new Line
                    {
                        X1 = y % 48 == 0 ? 2 : 4,
                        Y1 = RULER_WIDTH + y,
                        X2 = y % 48 == 0 ? RULER_WIDTH - 2 : RULER_WIDTH - 4,
                        Y2 = RULER_WIDTH + y,
                        Stroke = this.Foreground,
                        StrokeThickness = 1
                    };
                    rulerCanvas.Children.Add(line);
                }
            }

            Line leftLine = new Line
            {
                X1 = RULER_WIDTH - 1,
                Y1 = RULER_WIDTH - 1,
                X2 = RULER_WIDTH - 1,
                Y2 = rulerCanvas.ActualHeight,
                Stroke = this.Foreground,
                StrokeThickness = 2
            };
            rulerCanvas.Children.Add(leftLine);
        }
    }
}
