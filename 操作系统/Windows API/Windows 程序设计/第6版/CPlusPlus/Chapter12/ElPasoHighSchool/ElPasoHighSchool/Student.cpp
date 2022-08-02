#include "pch.h"
#include "Student.h"

using namespace ElPasoHighSchool;

using namespace Platform;

void Student::FullName::set(String^ value)
{
    if (fullName != value)
    {
        fullName = value;
        OnPropertyChanged("FullName");
    }
}

void Student::FirstName::set(String^ value)
{
    if (firstName != value)
    {
        firstName = value;
        OnPropertyChanged("FirstName");
    }
}

void Student::MiddleName::set(String^ value)
{
    if (middleName != value)
    {
        middleName = value;
        OnPropertyChanged("MiddleName");
    }
}

void Student::LastName::set(String^ value)
{
    if (lastName != value)
    {
        lastName = value;
        OnPropertyChanged("LastName");
    }
}

void Student::Sex::set(String^ value)
{
    if (sex != value)
    {
        sex = value;
        OnPropertyChanged("Sex");
    }
}

void Student::PhotoFilename::set(String^ value)
{
    if (photoFilename != value)
    {
        photoFilename = value;
        OnPropertyChanged("PhotoFilename");
    }
}

void Student::GradePointAverage::set(double value)
{
    if (gradePointAverage != value)
    {
        gradePointAverage = value;
        OnPropertyChanged("GradePointAverage");
    }
}
