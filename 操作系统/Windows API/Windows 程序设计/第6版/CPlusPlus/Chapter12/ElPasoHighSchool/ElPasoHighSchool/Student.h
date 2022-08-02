#pragma once

namespace ElPasoHighSchool
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class Student sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        Platform::String ^ fullName, ^ firstName, ^ middleName, ^ lastName, ^ sex, ^ photoFilename;
        double gradePointAverage;

    public:
        Student() {}
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ FullName
        {
            void set(Platform::String^);
            Platform::String^ get() { return fullName; }
        }

        property Platform::String^ FirstName
        {
            void set(Platform::String^);
            Platform::String^ get() { return firstName; }
        }

        property Platform::String^ MiddleName
        {
            void set(Platform::String^);
            Platform::String^ get() { return middleName; }
        }

        property Platform::String^ Sex
        {
            void set(Platform::String^);
            Platform::String^ get() { return sex; }
        }

        property Platform::String^ PhotoFilename
        {
            void set(Platform::String^);
            Platform::String^ get() { return photoFilename; }
        }

        property double GradePointAverage
        {
            void set(double);
            double get() { return gradePointAverage; }
        }

        property Platform::String^ LastName
        {
            void set(Platform::String^);
            Platform::String^ get() { return lastName; }
        }

    protected:
        void OnPropertyChanged(Platform::String^ propertyName)
        {
            PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }
    };
}