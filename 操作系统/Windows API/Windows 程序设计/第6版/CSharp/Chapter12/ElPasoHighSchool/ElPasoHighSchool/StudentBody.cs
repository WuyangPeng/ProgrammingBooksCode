using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ElPasoHighSchool
{
    public class StudentBody : INotifyPropertyChanged
    {
        string school;
        ObservableCollection<Student> students = new ObservableCollection<Student>();

        public event PropertyChangedEventHandler PropertyChanged;

        public string School
        {
            set { SetProperty<string>(ref school, value); }
            get { return school; }
        }

        public ObservableCollection<Student> Students
        {
            set { SetProperty<ObservableCollection<Student>>(ref students, value); }
            get { return students; }
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
