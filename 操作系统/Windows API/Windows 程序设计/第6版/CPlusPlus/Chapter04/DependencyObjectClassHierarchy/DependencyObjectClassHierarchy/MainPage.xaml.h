//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ClassAndSubclasses.h"

namespace DependencyObjectClassHierarchy
{
    public ref class MainPage sealed
    {
    private:
        ReflectionHelper::TypeInformation^ rootTypeInfo;
        Platform::Collections::Vector<ReflectionHelper::TypeInformation^>^ classes;
        Windows::UI::Xaml::Media::Brush^ highlightBrush;

    public:
        MainPage();

    private:
        void AddToClassList(Platform::Type^ sampleType);
        void AddToTree(ClassAndSubclasses^ node, Windows::Foundation::Collections::IVector<ReflectionHelper::TypeInformation^>^ classes);
        void Display(ClassAndSubclasses^ node, int indent);
    };
}
