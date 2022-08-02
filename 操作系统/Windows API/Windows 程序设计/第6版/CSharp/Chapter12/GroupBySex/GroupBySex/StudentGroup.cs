using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using ElPasoHighSchool;

namespace GroupBySex
{
    public class StudentGroup : INotifyPropertyChanged
    {
        string title;
        ObservableCollection<Student> students = new ObservableCollection<Student>();

        public event PropertyChangedEventHandler PropertyChanged;

        public StudentGroup()
        {
            this.Students = new ObservableCollection<Student>();
        }

        public string Title
        {
            set { SetProperty<string>(ref title, value); }
            get { return title; }
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
