using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.Storage;
using Windows.UI;

namespace FingerPaint
{
    public class AppSettings : INotifyPropertyChanged
    {
        // Application settings initial values
        string loadedFilePath = null;
        string loadedFilename = null;
        bool isImageModified = false;
        Color color = Colors.Blue;
        double thickness = 16;

        public event PropertyChangedEventHandler PropertyChanged;

        public AppSettings()
        {
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

            if (appData.Values.ContainsKey("LoadedFilePath"))
                this.LoadedFilePath = (string)appData.Values["LoadedFilePath"];

            if (appData.Values.ContainsKey("LoadedFilename"))
                this.LoadedFilename = (string)appData.Values["LoadedFilename"];

            if (appData.Values.ContainsKey("IsImageModified"))
                this.IsImageModified = (bool)appData.Values["IsImageModified"];

            if (appData.Values.ContainsKey("Color.Red") &&
                appData.Values.ContainsKey("Color.Green") &&
                appData.Values.ContainsKey("Color.Blue"))
            {
                this.Color = Color.FromArgb(255,
                                            (byte)appData.Values["Color.Red"],
                                            (byte)appData.Values["Color.Green"],
                                            (byte)appData.Values["Color.Blue"]);
            }

            if (appData.Values.ContainsKey("Thickness"))
                this.Thickness = (double)appData.Values["Thickness"];

        }

        public string LoadedFilePath
        {
            set { SetProperty<string>(ref loadedFilePath, value); }
            get { return loadedFilePath; }
        }

        public string LoadedFilename
        {
            set { SetProperty<string>(ref loadedFilename, value); }
            get { return loadedFilename; }
        }

        public bool IsImageModified
        {
            set { SetProperty<bool>(ref isImageModified, value); }
            get { return isImageModified; }
        }

        public Color Color
        {
            set { SetProperty<Color>(ref color, value); }
            get { return color; }
        }

        public double Thickness
        {
            set { SetProperty<double>(ref thickness, value); }
            get { return thickness; }
        }

        public void Save()
        {
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;
            appData.Values.Clear();
            appData.Values.Add("LoadedFilePath", this.LoadedFilePath);
            appData.Values.Add("LoadedFilename", this.LoadedFilename);
            appData.Values.Add("IsImageModified", this.IsImageModified);
            appData.Values.Add("Color.Red", this.Color.R);
            appData.Values.Add("Color.Green", this.Color.G);
            appData.Values.Add("Color.Blue", this.Color.B);
            appData.Values.Add("Thickness", this.Thickness);
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
