using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace Petzold.ProgrammingWindows6.Chapter11
{
    public class NewToggle : ContentControl
    {
        public event EventHandler CheckedChanged;
        Button uncheckButton, checkButton;

        static NewToggle()
        {
            CheckedContentProperty = DependencyProperty.Register("CheckedContent",
                typeof(object),
                typeof(NewToggle),
                new PropertyMetadata(null));

            IsCheckedProperty = DependencyProperty.Register("IsChecked",
                typeof(bool),
                typeof(NewToggle),
                new PropertyMetadata(false, OnCheckedChanged));
        }

        public NewToggle()
        {
            this.DefaultStyleKey = typeof(NewToggle);
        }

        public static DependencyProperty CheckedContentProperty { private set; get; }

        public static DependencyProperty IsCheckedProperty { private set; get; }

        public object CheckedContent
        {
            set { SetValue(CheckedContentProperty, value); }
            get { return GetValue(CheckedContentProperty); }
        }

        public bool IsChecked
        {
            set { SetValue(IsCheckedProperty, value); }
            get { return (bool)GetValue(IsCheckedProperty); }
        }

        protected override void OnApplyTemplate()
        {
            if (uncheckButton != null)
                uncheckButton.Click -= OnButtonClick;

            if (checkButton != null)
                checkButton.Click -= OnButtonClick;

            uncheckButton = GetTemplateChild("UncheckButton") as Button;
            checkButton = GetTemplateChild("CheckButton") as Button;

            if (uncheckButton != null)
                uncheckButton.Click += OnButtonClick;

            if (checkButton != null)
                checkButton.Click += OnButtonClick;

            base.OnApplyTemplate();
        }

        void OnButtonClick(object sender, RoutedEventArgs args)
        {
 	        this.IsChecked = sender == checkButton;
        }

        static void OnCheckedChanged(DependencyObject obj,
                                     DependencyPropertyChangedEventArgs args)
        {
            (obj as NewToggle).OnCheckedChanged(EventArgs.Empty);
        }

        protected virtual void OnCheckedChanged(EventArgs args)
        {
            VisualStateManager.GoToState(this, 
                                         this.IsChecked ? "Checked" : "Unchecked", 
                                         true);

            if (CheckedChanged != null)
                CheckedChanged(this, args);
        }
    }
}
