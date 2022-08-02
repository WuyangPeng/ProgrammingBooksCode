#pragma once

namespace GroupBySex
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class StudentGroup sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        Platform::String ^ title;
        Windows::Foundation::Collections::IVector<ElPasoHighSchool::Student^>^ students;

    public:
        StudentGroup();
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ Title
        {
            void set(Platform::String^);
            Platform::String^ get() { return title; }
        }

        property Windows::Foundation::Collections::IVector<ElPasoHighSchool::Student^>^ Students
        {
            void set(Windows::Foundation::Collections::IVector<ElPasoHighSchool::Student^>^);
            Windows::Foundation::Collections::IVector<ElPasoHighSchool::Student^>^ get() { return students; }
        }

    protected:
        void OnPropertyChanged(Platform::String^ propertyName)
        {
            PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }
    };
}