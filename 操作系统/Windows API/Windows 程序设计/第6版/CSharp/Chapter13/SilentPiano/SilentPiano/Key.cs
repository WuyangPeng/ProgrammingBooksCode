using System.Collections.Generic;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace SilentPiano
{
    public class Key : Control
    {
        static readonly DependencyProperty isPressedProperty =
                DependencyProperty.Register("IsPressed",
                        typeof(bool), typeof(Key), 
                        new PropertyMetadata(false, OnIsPressedChanged));

        List<uint> pointerList = new List<uint>();

        public static DependencyProperty IsPressedProperty 
        {
            get { return isPressedProperty; }
        }

        public bool IsPressed
        {
            set { SetValue(IsPressedProperty, value); }
            get { return (bool)GetValue(IsPressedProperty); }
        }

        protected override void OnPointerEntered(PointerRoutedEventArgs args)
        {
            if (args.Pointer.IsInContact)
                AddToList(args.Pointer.PointerId);
            base.OnPointerEntered(args);
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            AddToList(args.Pointer.PointerId);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            RemoveFromList(args.Pointer.PointerId);
            base.OnPointerReleased(args);
        }

        protected override void OnPointerExited(PointerRoutedEventArgs args)
        {
            RemoveFromList(args.Pointer.PointerId);
            base.OnPointerExited(args);
        }

        void AddToList(uint id)
        {
            if (!pointerList.Contains(id))
                pointerList.Add(id);

            CheckList();
        }

        void RemoveFromList(uint id)
        {
            if (pointerList.Contains(id))
                pointerList.Remove(id);

            CheckList();
        }

        void CheckList()
        {
            this.IsPressed = pointerList.Count > 0;
        }

        static void OnIsPressedChanged(DependencyObject obj, 
                                       DependencyPropertyChangedEventArgs args)
        {
            VisualStateManager.GoToState(obj as Key, 
                            (bool)args.NewValue ? "Pressed" : "Normal", false);
        }
    }
}
