using System.Collections.Generic;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace PointerLog
{
    public sealed partial class LoggerControl : UserControl
    {
        class PointerInfo
        {
            public StackPanel stackPanel;
            public string repeatEvent;
            public TextBlock repeatTextBlock;
        };

        Dictionary<uint, PointerInfo> pointerDictionary = new Dictionary<uint, PointerInfo>();

        public LoggerControl()
        {
            this.InitializeComponent();
        }

        public bool CaptureOnPress { set; get; }

        protected override void OnPointerEntered(PointerRoutedEventArgs args)
        {
            Log("Entered", args);
            base.OnPointerEntered(args);
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            if (this.CaptureOnPress)
                CapturePointer(args.Pointer);

            Log("Pressed", args);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            Log("Moved", args);
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            Log("Released", args);
            base.OnPointerReleased(args);
        }

        protected override void OnPointerExited(PointerRoutedEventArgs args)
        {
            Log("Exited", args);
            base.OnPointerExited(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            Log("CaptureLost", args);
            base.OnPointerCaptureLost(args);
        }

        protected override void OnPointerCanceled(PointerRoutedEventArgs args)
        {
            Log("Canceled", args);
            base.OnPointerCanceled(args);
        }

        protected override void OnPointerWheelChanged(PointerRoutedEventArgs args)
        {
            Log("WheelChanged", args);
            base.OnPointerWheelChanged(args);
        }

        void Log(string eventName, PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            PointerInfo pointerInfo;

            if (pointerDictionary.ContainsKey(id))
            {
                pointerInfo = pointerDictionary[id];
            }
            else
            {
                // New ID, so new StackPanel and header
                TextBlock header = new TextBlock
                {
                    Text = args.Pointer.PointerId + " - " + args.Pointer.PointerDeviceType,
                    FontWeight = FontWeights.Bold
                };
                StackPanel stackPanel = new StackPanel();
                stackPanel.Children.Add(header);

                // New PointerInfo for dictionary
                pointerInfo = new PointerInfo
                {
                    stackPanel = stackPanel
                };
                pointerDictionary.Add(id, pointerInfo);

                // New column in the Grid for the StackPanel
                ColumnDefinition coldef = new ColumnDefinition
                {
                    Width = new GridLength(1, GridUnitType.Star)
                };
                contentGrid.ColumnDefinitions.Add(coldef);
                Grid.SetColumn(stackPanel, contentGrid.ColumnDefinitions.Count - 1);
                contentGrid.Children.Add(stackPanel);
            }

            // Don't repeat PointerMoved and PointerWheelChanged events
            TextBlock txtblk = null;

            if (eventName == pointerInfo.repeatEvent)
            {
                txtblk = pointerInfo.repeatTextBlock;
            }
            else
            {
                txtblk = new TextBlock();
                pointerInfo.stackPanel.Children.Add(txtblk);
            }

            txtblk.Text = eventName + " ";

            if (eventName == "WheelChanged")
            {
                txtblk.Text += args.GetCurrentPoint(this).Properties.MouseWheelDelta;
            }
            else
            {
                txtblk.Text += args.GetCurrentPoint(this).Position;
            }

            txtblk.Text += args.Pointer.IsInContact ? " C" : "";
            txtblk.Text += args.Pointer.IsInRange ? " R" : "";

            if (eventName == "Moved" || eventName == "WheelChanged")
            {
                pointerInfo.repeatEvent = eventName;
                pointerInfo.repeatTextBlock = txtblk;
            }
            else
            {
                pointerInfo.repeatEvent = null;
                pointerInfo.repeatTextBlock = null;
            }
        }

        public void Clear()
        {
            contentGrid.ColumnDefinitions.Clear();
            contentGrid.Children.Clear();
            pointerDictionary.Clear();
        }
    }
}
