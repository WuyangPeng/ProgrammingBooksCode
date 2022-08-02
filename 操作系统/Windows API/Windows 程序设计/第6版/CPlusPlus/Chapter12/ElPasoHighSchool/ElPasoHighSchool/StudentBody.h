#pragma once

#include "Student.h"

namespace ElPasoHighSchool
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class StudentBody sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        Platform::String^ school;
        Windows::Foundation::Collections::IVector<Student^>^ students;

    public:
        StudentBody();
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ School
        {
            void set(Platform::String^);
            Platform::String^ get() { return school; }
        }

        property Windows::Foundation::Collections::IVector<Student^>^ Students
        {
            void set(Windows::Foundation::Collections::IVector<Student^>^);
            Windows::Foundation::Collections::IVector<Student^>^ get() { return students; }
        }

    protected:
        void OnPropertyChanged(Platform::String^ propertyName)
        {
            PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }
    };
}