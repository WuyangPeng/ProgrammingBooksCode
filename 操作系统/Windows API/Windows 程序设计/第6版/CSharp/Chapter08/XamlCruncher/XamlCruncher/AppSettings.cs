using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.Storage;
using Windows.UI.Xaml.Controls;

namespace XamlCruncher
{
    public class AppSettings : INotifyPropertyChanged
    {
        // Application settings initial values
        EditOrientation editOrientation = EditOrientation.Left;
        Orientation orientation = Orientation.Horizontal;
        bool swapEditAndDisplay = false;
        bool autoParsing = false;
        bool showRuler = false;
        bool showGridLines = false;
        double fontSize = 18;
        int tabSpaces = 4;

        public event PropertyChangedEventHandler PropertyChanged;

        public AppSettings()
        {
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

            if (appData.Values.ContainsKey("EditOrientation"))
                this.EditOrientation = (EditOrientation)(int)appData.Values["EditOrientation"];

            if (appData.Values.ContainsKey("AutoParsing"))
                this.AutoParsing = (bool)appData.Values["AutoParsing"];

            if (appData.Values.ContainsKey("ShowRuler"))
                this.ShowRuler = (bool)appData.Values["ShowRuler"];

            if (appData.Values.ContainsKey("ShowGridLines"))
                this.ShowGridLines = (bool)appData.Values["ShowGridLines"];

            if (appData.Values.ContainsKey("FontSize"))
                this.FontSize = (double)appData.Values["FontSize"];

            if (appData.Values.ContainsKey("TabSpaces"))
                this.TabSpaces = (int)appData.Values["TabSpaces"];
        }

        public EditOrientation EditOrientation
        {
            set
            {
                if (SetProperty<EditOrientation>(ref editOrientation, value))
                {
                    switch (editOrientation)
                    {
                        case EditOrientation.Left:
                            this.Orientation = Orientation.Horizontal;
                            this.SwapEditAndDisplay = false;
                            break;

                        case EditOrientation.Top:
                            this.Orientation = Orientation.Vertical;
                            this.SwapEditAndDisplay = false;
                            break;

                        case EditOrientation.Right:
                            this.Orientation = Orientation.Horizontal;
                            this.SwapEditAndDisplay = true;
                            break;

                        case EditOrientation.Bottom:
                            this.Orientation = Orientation.Vertical;
                            this.SwapEditAndDisplay = true;
                            break;
                    }
                }
            }
            get { return editOrientation; }
        }

        public Orientation Orientation
        {
            protected set { SetProperty<Orientation>(ref orientation, value); }
            get { return orientation; }
        }

        public bool SwapEditAndDisplay
        {
            protected set { SetProperty<bool>(ref swapEditAndDisplay, value); }
            get { return swapEditAndDisplay; }
        }

        public bool AutoParsing
        {
            set { SetProperty<bool>(ref autoParsing, value); }
            get { return autoParsing; }
        }

        public bool ShowRuler
        {
            set { SetProperty<bool>(ref showRuler, value); }
            get { return showRuler; }
        }

        public bool ShowGridLines
        {
            set { SetProperty<bool>(ref showGridLines, value); }
            get { return showGridLines; }
        }

        public double FontSize
        {
            set { SetProperty<double>(ref fontSize, value); }
            get { return fontSize; }
        }

        public int TabSpaces
        {
            set { SetProperty<int>(ref tabSpaces, value); }
            get { return tabSpaces; }
        }

        public void Save()
        {
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;
            appData.Values.Clear();
            appData.Values.Add("EditOrientation", (int)this.EditOrientation);
            appData.Values.Add("AutoParsing", this.AutoParsing);
            appData.Values.Add("ShowRuler", this.ShowRuler);
            appData.Values.Add("ShowGridLines", this.ShowGridLines);
            appData.Values.Add("FontSize", this.FontSize);
            appData.Values.Add("TabSpaces", this.TabSpaces);
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