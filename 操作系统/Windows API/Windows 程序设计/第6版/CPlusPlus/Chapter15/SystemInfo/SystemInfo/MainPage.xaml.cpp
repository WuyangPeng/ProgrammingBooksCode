//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SystemInfo;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    // Windows.h included in pch.h
    SYSTEM_INFO systemInfo;
    GetNativeSystemInfo(&systemInfo);

    processorArchitecture->Text = ((ProcessorType)systemInfo.wProcessorArchitecture).ToString();
    pageSize->Text = systemInfo.dwPageSize.ToString();
    minAppAddr->Text = ToHexString((uint64)systemInfo.lpMinimumApplicationAddress);
    maxAppAddr->Text = ToHexString((uint64)systemInfo.lpMaximumApplicationAddress);
    activeProcessorMask->Text = ToHexString(systemInfo.dwActiveProcessorMask);
    numberProcessors->Text = systemInfo.dwNumberOfProcessors.ToString();
    allocationGranularity->Text = systemInfo.dwAllocationGranularity.ToString();
    processorLevel->Text = systemInfo.wProcessorLevel.ToString();
    processorRevision->Text = ToHexString(systemInfo.wProcessorRevision);
}

String^ MainPage::ToHexString(uint64 value)
{
    wchar_t str[17];
    swprintf(str, sizeof(str) / sizeof(str[0]), L"%X", value);
    return ref new String(str);
}
