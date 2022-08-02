#include "pch.h"
#include "StudentBody.h"

using namespace ElPasoHighSchool;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

StudentBody::StudentBody()
{
    this->Students = ref new Vector<Student^>();
}

void StudentBody::School::set(String^ value)
{
    if (school != value)
    {
        school = value;
        OnPropertyChanged("School");
    }
}

void StudentBody::Students::set(IVector<Student^>^ value)
{
    if (students != value)
    {
        students = value;
        OnPropertyChanged("Students");
    }
}
