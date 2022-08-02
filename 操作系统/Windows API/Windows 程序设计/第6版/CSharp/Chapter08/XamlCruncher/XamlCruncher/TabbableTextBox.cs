using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace XamlCruncher
{
    public class TabbableTextBox : TextBox
    {
        static TabbableTextBox()
        {
            TabSpacesProperty =
                DependencyProperty.Register("TabSpaces",
                    typeof(int), typeof(TabbableTextBox),
                    new PropertyMetadata(4));
        }

        public static DependencyProperty TabSpacesProperty { private set; get; }

        public int TabSpaces
        {
            set { SetValue(TabSpacesProperty, value); }
            get { return (int)GetValue(TabSpacesProperty); }
        }

        public bool IsModified { set; get; }

        protected override void OnKeyDown(KeyRoutedEventArgs args)
        {
            this.IsModified = true;

            if (args.Key == VirtualKey.Tab)
            {
                int line, col;
                GetPositionFromIndex(this.SelectionStart, out line, out col);
                int insertCount = this.TabSpaces - col % this.TabSpaces;
                this.SelectedText = new string(' ', insertCount);
                this.SelectionStart += insertCount;
                this.SelectionLength = 0;
                args.Handled = true;
                return;
            }
            base.OnKeyDown(args);
        }

        public void GetPositionFromIndex(int index, out int line, out int col)
        {
            if (index > Text.Length)
            {
                line = col = -1;
                return;
            }

            line = col = 0;
            int i = 0;

            while (i < index)
            {
                if (Text[i] == '\n')
                {
                    line++;
                    col = 0;
                }
                else if (Text[i] == '\r')
                {
                    index++;
                }
                else
                {
                    col++;
                };
                i++;
            }
        }
    }
}
