#include "pch.h"
#include "StudentGroups.h"

using namespace GroupBySex;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Data;

using namespace ElPasoHighSchool;

StudentGroups::StudentGroups()
{
    this->Groups = ref new Vector<StudentGroup^>();
}

void StudentGroups::Source::set(StudentBodyPresenter^ value)
{
    if (value != nullptr)
    {
        presenter = value;
        presenter->PropertyChanged += ref new PropertyChangedEventHandler(this, &StudentGroups::OnHighSchoolPropertyChanged);
    }
}

void StudentGroups::Groups::set(IVector<StudentGroup^>^ value)
{
    if (groups != value)
    {
        groups = value;
        OnPropertyChanged("Groups");
    }
}

void StudentGroups::OnHighSchoolPropertyChanged(Object^ sender, PropertyChangedEventArgs^ args)
{
    if (args->PropertyName == "StudentBody")
    {
        this->Groups->Clear();

        if (presenter->StudentBody != nullptr)
        {
            StudentGroup^ males = ref new StudentGroup();
            males->Title = "Male";
            this->Groups->Append(males);

            StudentGroup^ females = ref new StudentGroup();
            females->Title = "Female";
            this->Groups->Append(females);

            for each (Student^ student in presenter->StudentBody->Students)
            {
                if (student->Sex == "Male")
                    males->Students->Append(student);
                else
                    females->Students->Append(student);
            }
        }
    }
}
