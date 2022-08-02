#pragma once

namespace PrintableTomKitten
{
    public ref class CustomPageRange sealed
    {
    private:
        struct PageRange
        {
            int From;
            int To;
        };
        Platform::Collections::Vector<int>^ pageMapping;

    public:
        CustomPageRange(Platform::String^ str, int maxPageNumber);
        bool Atoi(wchar_t * str, int * value);
        property Windows::Foundation::Collections::IVector<int>^ PageMapping
        {
            Windows::Foundation::Collections::IVector<int>^ get();
        }
        property bool IsValid
        {
            bool get();
        }
    };
}
