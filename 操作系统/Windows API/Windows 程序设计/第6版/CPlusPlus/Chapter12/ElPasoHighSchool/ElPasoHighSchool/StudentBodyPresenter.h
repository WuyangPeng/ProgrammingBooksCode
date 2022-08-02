#pragma once

#include "Student.h"
#include "StudentBody.h"

namespace ElPasoHighSchool
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class StudentBodyPresenter sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        StudentBody^ studentBody;

    public:
        StudentBodyPresenter();
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property StudentBody^ StudentBody
        {
            void set(ElPasoHighSchool::StudentBody^);
            ElPasoHighSchool::StudentBody^ get() { return studentBody; }
        }

    private:
        ElPasoHighSchool::StudentBody^ CreateStudentBody(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        Platform::String^ CreateSchool(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        Windows::Foundation::Collections::IVector<Student^>^ CreateStudents(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        Student^ CreateStudent(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        LPCWSTR GetLocalName(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        Platform::String^ GetStringContent(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader);
        double GetDoubleContent(Microsoft::WRL::ComPtr<IXmlReader> pXmlReader); 
        void OnTimerTick(Platform::Object^ sender, Platform::Object^ args);

    protected:
        void OnPropertyChanged(Platform::String^ propertyName)
        {
            PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }
    };
}