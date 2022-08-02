#pragma once

#include "StudentGroup.h"

namespace GroupBySex
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class StudentGroups sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        ElPasoHighSchool::StudentBodyPresenter^ presenter;
        Windows::Foundation::Collections::IVector<StudentGroup^>^ groups;

    public:
        StudentGroups();
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property ElPasoHighSchool::StudentBodyPresenter^ Source
        {
            void set(ElPasoHighSchool::StudentBodyPresenter^);
        }

        property Windows::Foundation::Collections::IVector<StudentGroup^>^ Groups
        {
            void set(Windows::Foundation::Collections::IVector<StudentGroup^>^);
            Windows::Foundation::Collections::IVector<StudentGroup^>^ get() { return groups; }
        }

    private:
        void OnHighSchoolPropertyChanged(Platform::Object^ sender, Windows::UI::Xaml::Data::PropertyChangedEventArgs^ args);

    protected:
        void OnPropertyChanged(Platform::String^ propertyName)
        {
            PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }
    };
}