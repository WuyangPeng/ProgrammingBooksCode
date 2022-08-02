#include "pch.h"
#include "StudentGroup.h"

using namespace GroupBySex;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

using namespace ElPasoHighSchool;

StudentGroup::StudentGroup()
{
    this->Students = ref new Vector<Student^>();
}

void StudentGroup::Title::set(String^ value)
{
    if (title != value)
    {
        title = value;
        OnPropertyChanged("Title");
    }
}

void StudentGroup::Students::set(IVector<Student^>^ value)
{
    if (students != value)
    {
        students = value;
        OnPropertyChanged("Students");
    }
}
