using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.UI;

namespace ColorTextBoxesWithEvents
{
    public class RgbViewModel : INotifyPropertyChanged
    {
        double red, green, blue;
        Color color = Color.FromArgb(255, 0, 0, 0);

        public event PropertyChangedEventHandler PropertyChanged;

        public double Red
        {
            set
            {
                if (SetProperty<double>(ref red, value, "Red"))
                    Calculate();
            }
            get
            {
                return red;
            }
        }

        public double Green
        {
            set
            {
                if (SetProperty<double>(ref green, value))
                    Calculate();
            }
            get
            {
                return green;
            }
        }

        public double Blue
        {
            set
            {
                if (SetProperty<double>(ref blue, value))
                    Calculate();
            }
            get
            {
                return blue;
            }
        }

        public Color Color
        {
            set
            {
                if (SetProperty<Color>(ref color, value))
                {
                    this.Red = value.R;
                    this.Green = value.G;
                    this.Blue = value.B;
                }
            }
            get
            {
                return color;
            }
        }

        void Calculate()
        {
            this.Color = Color.FromArgb(255, (byte)this.Red, (byte)this.Green, (byte)this.Blue);
        }

        protected bool SetProperty<T>(ref T storage, T value,
                                      [CallerMemberName] string propertyName = null)
        {
            if (object.Equals(storage, value))
                return false;

            storage = value;
            OnPropertyChanged(propertyName);
            return true;
        }

        protected void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
