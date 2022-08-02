using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace SegoeSymbols
{
    public sealed partial class MainPage : Page
    {
        const int CellSize = 36;
        const int LineLength = (CellSize + 1) * 16 + 18;
        FontFamily symbolFont = new FontFamily("Segoe UI Symbol");

        TextBlock[] txtblkColumnHeads = new TextBlock[16];
        TextBlock[,] txtblkCharacters = new TextBlock[16, 16];

        public MainPage()
        {
            this.InitializeComponent();

            for (int row = 0; row < 34; row++)
            {
                RowDefinition rowdef = new RowDefinition();

                if (row == 0 || row % 2 == 1)
                    rowdef.Height = GridLength.Auto;
                else
                    rowdef.Height = new GridLength(CellSize, GridUnitType.Pixel);
                    
                characterGrid.RowDefinitions.Add(rowdef);

                if (row != 0 && row % 2 == 0)
                {
                    TextBlock txtblk = new TextBlock
                    {
                        Text = (row / 2 - 1).ToString("X1"),
                        VerticalAlignment = VerticalAlignment.Center
                    };
                    Grid.SetRow(txtblk, row);
                    Grid.SetColumn(txtblk, 0);
                    characterGrid.Children.Add(txtblk);
                }

                if (row % 2 == 1)
                {
                    Rectangle rectangle = new Rectangle
                    {
                        Stroke = this.Foreground,
                        StrokeThickness = row == 1 || row == 33 ? 1.5 : 0.5,
                        Height = 1
                    };
                    Grid.SetRow(rectangle, row);
                    Grid.SetColumn(rectangle, 0);
                    Grid.SetColumnSpan(rectangle, 34);
                    characterGrid.Children.Add(rectangle);
                }
            }

            for (int col = 0; col < 34; col++)
            {
                ColumnDefinition coldef = new ColumnDefinition();

                if (col == 0 || col % 2 == 1)
                    coldef.Width = GridLength.Auto;
                else
                    coldef.Width = new GridLength(CellSize);
                    
                characterGrid.ColumnDefinitions.Add(coldef);

                if (col != 0 && col % 2 == 0)
                {
                    TextBlock txtblk = new TextBlock 
                    { 
                        Text = "00" + (col / 2 - 1).ToString("X1") + "_", 
                        HorizontalAlignment = HorizontalAlignment.Center
                    };
                    Grid.SetRow(txtblk, 0);
                    Grid.SetColumn(txtblk, col);
                    characterGrid.Children.Add(txtblk);
                    txtblkColumnHeads[col / 2 - 1] = txtblk;
                }

                if (col % 2 == 1)
                {
                    Rectangle rectangle = new Rectangle
                    {
                        Stroke = this.Foreground,
                        StrokeThickness = col == 1 || col == 33 ? 1.5 : 0.5,
                        Width = 1
                    };
                    Grid.SetRow(rectangle, 0);
                    Grid.SetColumn(rectangle, col);
                    Grid.SetRowSpan(rectangle, 34);
                    characterGrid.Children.Add(rectangle);
                }
            }

            for (int col = 0; col < 16; col++)
                for (int row = 0; row < 16; row++)
                {
                    TextBlock txtblk = new TextBlock
                    {
                        Text = ((char)(16 * col + row)).ToString(),
                        FontFamily = symbolFont,
                        FontSize = 24,
                        HorizontalAlignment = HorizontalAlignment.Center,
                        VerticalAlignment = VerticalAlignment.Center
                    };
                    Grid.SetRow(txtblk, 2 * row + 2);
                    Grid.SetColumn(txtblk, 2 * col + 2);
                    characterGrid.Children.Add(txtblk);
                    txtblkCharacters[col, row] = txtblk;
                }
        }

        void OnSliderValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            int baseCode = 256 * (int)args.NewValue;

            for (int col = 0; col < 16; col++)
            {
                txtblkColumnHeads[col].Text = (baseCode / 16 + col).ToString("X3") + "_";

                for (int row = 0; row < 16; row++)
                {
                    int code = baseCode + 16 * col + row;
                    string strChar = null;

                    if (code <= 0x0FFFF)
                    {
                        strChar = ((char)code).ToString();
                    }
                    else
                    {
                        code -= 0x10000;
                        int lead = 0xD800 + code / 1024;
                        int trail = 0xDC00 + code % 1024;
                        strChar = ((char)lead).ToString() + (char)trail;
                    }
                    txtblkCharacters[col, row].Text = strChar;
                }
            }
        }
    }
}
