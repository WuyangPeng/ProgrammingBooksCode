using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using ElPasoHighSchool;

namespace GroupBySex
{
    public class StudentGroups : INotifyPropertyChanged
    {
        StudentBodyPresenter presenter;
        ObservableCollection<StudentGroup> groups = new ObservableCollection<StudentGroup>();

        public event PropertyChangedEventHandler PropertyChanged;

        public StudentBodyPresenter Source
        {
            set
            {
                if (value != null)
                {
                    presenter = value;
                    presenter.PropertyChanged += OnHighSchoolPropertyChanged;
                }
            }
        }

        void OnHighSchoolPropertyChanged(object sender, PropertyChangedEventArgs args)
        {
 	        if (args.PropertyName == "StudentBody" && presenter.StudentBody != null)
            {
                this.Groups = new ObservableCollection<StudentGroup>();
                this.Groups.Add(new StudentGroup { Title = "Male" });
                this.Groups.Add(new StudentGroup { Title = "Female" });
    
                foreach (Student student in presenter.StudentBody.Students)
                    if (student.Sex == "Male")
                        this.Groups[0].Students.Add(student);
                    else
                        this.Groups[1].Students.Add(student);
            }
        }

        public ObservableCollection<StudentGroup> Groups
        {
            set { SetProperty<ObservableCollection<StudentGroup>>(ref groups, value); }
            get { return groups; }
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
