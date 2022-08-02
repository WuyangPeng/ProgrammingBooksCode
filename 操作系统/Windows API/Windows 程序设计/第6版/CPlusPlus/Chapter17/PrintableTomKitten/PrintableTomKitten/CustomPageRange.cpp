#include "pch.h"
#include "CustomPageRange.h"

using namespace PrintableTomKitten;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

CustomPageRange::CustomPageRange(String^ str, int maxPageNumber)
{
    std::vector<PageRange> pageRanges;
    wchar_t str2[1000];
    wcscpy_s(str2, 1000, str->Data());
    wchar_t* context;
    wchar_t* strRange = wcstok_s(str2, L" ,", &context);

    while (strRange != nullptr)
    {
        int dashIndex = wcscspn(strRange, L"-");

        // Just one page number
        if (dashIndex == wcslen(strRange))
        {
            int page = 0;
            if (Atoi(strRange, &page) &&
                page > 0 && page <= maxPageNumber)
            {
                PageRange pageRange = { page, page };
                pageRanges.push_back(pageRange);
            }
            else
            {
                return;
            }
        }
        // Two page numbers separated by a dash
        else
        {
            strRange[dashIndex] = '\0';
            int from = 0;
            int to = 0;

            if (Atoi(strRange, &from) &&
                Atoi(strRange + dashIndex + 1, &to) &&
                from > 0 && from <= maxPageNumber &&
                to > 0 && to <= maxPageNumber &&
                from <= to)
            {
                PageRange pageRange = { from, to };
                pageRanges.push_back(pageRange);
            }
            else
            {
                return;
            }
        }
        strRange = wcstok_s(nullptr, L" ,", &context);
    }

    if (pageRanges.size() == 0)
        return;

    // If we made it to this, the input string is valid
    this->pageMapping = ref new Vector<int>();

    // Define a mapping to page numbers
    for (unsigned int index = 0; index < pageRanges.size(); index++)
        for (int page = pageRanges[index].From; page <= pageRanges[index].To; page ++)
            pageMapping->Append(page);
}

bool CustomPageRange::Atoi(wchar_t * str, int * value)
{
    wchar_t overflow[10];
    return 1 == swscanf_s(str, L"%i %s", value, overflow, 10);
}

IVector<int>^ CustomPageRange::PageMapping::get()
{
    return pageMapping;
}

bool CustomPageRange::IsValid::get()
{
    return this->PageMapping != nullptr;
}
