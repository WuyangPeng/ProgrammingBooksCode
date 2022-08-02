using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Media3D;

namespace NonAffineStretch
{
    public sealed partial class DisplayMatrix3D : UserControl
    {
        static DependencyProperty matrix3DProperty =
            DependencyProperty.Register("Matrix3D",
                typeof(Matrix3D), typeof(DisplayMatrix3D),
                new PropertyMetadata(Matrix3D.Identity, OnPropertyChanged));

        public DisplayMatrix3D()
        {
            this.InitializeComponent();
        }

        public static DependencyProperty Matrix3DProperty
        {
            get { return matrix3DProperty; }
        }

        public Matrix3D Matrix3D
        {
            set { SetValue(Matrix3DProperty, value); }
            get { return (Matrix3D)GetValue(Matrix3DProperty); }
        }

        static void OnPropertyChanged(DependencyObject obj, 
                                      DependencyPropertyChangedEventArgs args)
        {
            (obj as DisplayMatrix3D).OnPropertyChanged(args);
        }

        void OnPropertyChanged(DependencyPropertyChangedEventArgs args)
        {
            m11.Text = this.Matrix3D.M11.ToString("F3");
            m12.Text = this.Matrix3D.M12.ToString("F3");
            m13.Text = this.Matrix3D.M13.ToString("F3");
            m14.Text = this.Matrix3D.M14.ToString("F6");

            m21.Text = this.Matrix3D.M21.ToString("F3");
            m22.Text = this.Matrix3D.M22.ToString("F3");
            m23.Text = this.Matrix3D.M23.ToString("F3");
            m24.Text = this.Matrix3D.M24.ToString("F6");

            m31.Text = this.Matrix3D.M31.ToString("F3");
            m32.Text = this.Matrix3D.M32.ToString("F3");
            m33.Text = this.Matrix3D.M33.ToString("F3");
            m34.Text = this.Matrix3D.M34.ToString("F6");

            m41.Text = this.Matrix3D.OffsetX.ToString("F0");
            m42.Text = this.Matrix3D.OffsetY.ToString("F0");
            m43.Text = this.Matrix3D.OffsetZ.ToString("F0");
            m44.Text = this.Matrix3D.M44.ToString("F0");
        }
    }
}
