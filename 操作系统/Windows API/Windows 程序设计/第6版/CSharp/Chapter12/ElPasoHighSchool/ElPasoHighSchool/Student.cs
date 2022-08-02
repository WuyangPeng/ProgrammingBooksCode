using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace ElPasoHighSchool
{
    public class Student : INotifyPropertyChanged
    {
        string fullName, firstName, middleName, lastName, sex, photoFilename;
        double gradePointAverage;

        public event PropertyChangedEventHandler PropertyChanged;

        public string FullName
        {
            set { SetProperty<string>(ref fullName, value); }
            get { return fullName; }
        }

        public string FirstName
        {
            set { SetProperty<string>(ref firstName, value); }
            get { return firstName; }
        }

        public string MiddleName
        {
            set { SetProperty<string>(ref middleName, value); }
            get { return middleName; }
        }

        public string LastName
        {
            set { SetProperty<string>(ref lastName, value); }
            get { return lastName; }
        }

        public string Sex
        {
            set { SetProperty<string>(ref sex, value); }
            get { return sex; }
        }

        public string PhotoFilename
        {
            set { SetProperty<string>(ref photoFilename, value); }
            get { return photoFilename; }
        }

        public double GradePointAverage
        {
            set { SetProperty<double>(ref gradePointAverage, value); }
            get { return gradePointAverage; }
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
