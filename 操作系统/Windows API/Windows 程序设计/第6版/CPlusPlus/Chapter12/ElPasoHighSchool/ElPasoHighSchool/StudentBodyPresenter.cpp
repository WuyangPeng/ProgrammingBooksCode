#include "pch.h"
#include "StudentBodyPresenter.h"

using namespace ElPasoHighSchool;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;

StudentBodyPresenter::StudentBodyPresenter()
{
    // Download XML file
    Uri^ uri = ref new Uri("http://www.charlespetzold.com/Students/students.xml");
    RandomAccessStreamReference^ streamRef = RandomAccessStreamReference::CreateFromUri(uri);
    task<IRandomAccessStreamWithContentType^> openReadTask = create_task(streamRef->OpenReadAsync());
    openReadTask.then([this](IRandomAccessStreamWithContentType^ stream)
    {
        // Create a COM IStream object from the IRandomAccessStreamWithContentType
        ComPtr<IStream> pStream;
        HRESULT hr = CreateStreamOverRandomAccessStream(stream, __uuidof(IStream), &pStream);

        if (FAILED(hr))
            throw ref new COMException(hr, "CreateStreamOverRandomAccessStream failure");
        
        // Create a COM IXmlReader object
        ComPtr<IXmlReader> pXmlReader;
        hr = CreateXmlReader(__uuidof(IXmlReader), &pXmlReader, nullptr);

        if (FAILED(hr))
            throw ref new COMException(hr, "CreateXmlReader failure");

        hr = pXmlReader->SetInput(pStream.Get());

        if (FAILED(hr))
            throw ref new COMException(hr, "XmlReader->SetInput failure");

        // Deserialize XML
        XmlNodeType xmlNodeType;
        while (S_OK == pXmlReader->Read(&xmlNodeType))
        {
            // Look for StudentBody element
            if (xmlNodeType == XmlNodeType_Element)
            {
                LPCWSTR pName = GetLocalName(pXmlReader);

                if (wcscmp(pName, L"StudentBody") == 0)
                {
                    this->StudentBody = CreateStudentBody(pXmlReader);

                    // Set a timer for random changes
                    TimeSpan timeSpan;
                    timeSpan.Duration = 1000000;    // 0.1 seconds

                    DispatcherTimer^ timer = ref new DispatcherTimer();
                    timer->Interval = timeSpan;
                    timer->Tick += ref new EventHandler<Object^>(this, &StudentBodyPresenter::OnTimerTick);
                    timer->Start();
                }
            }
        }
    });
}

void StudentBodyPresenter::StudentBody::set(ElPasoHighSchool::StudentBody^ value)
{
    if (studentBody != value)
    {
        studentBody = value;
        OnPropertyChanged("StudentBody");
    }
}

StudentBody^ StudentBodyPresenter::CreateStudentBody(ComPtr<IXmlReader> pXmlReader)
{
    ElPasoHighSchool::StudentBody^ studentBody = ref new ElPasoHighSchool::StudentBody();

    XmlNodeType xmlNodeType;
    while (S_OK == pXmlReader->Read(&xmlNodeType))
    {
        if (xmlNodeType == XmlNodeType_Element)
        {
            LPCWSTR pName = GetLocalName(pXmlReader);

            // Search for School element
            if (wcscmp(pName, L"School") == 0)
            {
                studentBody->School = GetStringContent(pXmlReader);
            }

            // Search for Students element
            else if (wcscmp(pName, L"Students") == 0)
            {
                studentBody->Students = CreateStudents(pXmlReader);
            }
        }
        else if (xmlNodeType == XmlNodeType_EndElement)
        {
            break;
        }
    }
    return studentBody;
}

IVector<Student^>^ StudentBodyPresenter::CreateStudents(ComPtr<IXmlReader> pXmlReader)
{
    IVector<Student^>^ students = ref new Vector<Student^>();

    XmlNodeType xmlNodeType;
    while (S_OK == pXmlReader->Read(&xmlNodeType))
    {
        if (xmlNodeType == XmlNodeType_Element)
        {
            LPCWSTR pName = GetLocalName(pXmlReader);

            // Search for Student element
            if (wcscmp(pName, L"Student") == 0)
            {
                students->Append(CreateStudent(pXmlReader));
            }
        }
        else if (xmlNodeType == XmlNodeType_EndElement)
        {
            break;
        }
    }
    return students;
}

Student^ StudentBodyPresenter::CreateStudent(ComPtr<IXmlReader> pXmlReader)
{
    Student^ student = ref new Student();

    XmlNodeType xmlNodeType;
    while (S_OK == pXmlReader->Read(&xmlNodeType))
    {
        if (xmlNodeType == XmlNodeType_Element)
        {
            LPCWSTR pName = GetLocalName(pXmlReader);

            // Search for sub-elements of Student
            if (wcscmp(pName, L"FullName") == 0)
                student->FullName = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"FirstName") == 0)
                student->FirstName = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"MiddleName") == 0)
                student->MiddleName = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"LastName") == 0)
                student->LastName = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"Sex") == 0)
                student->Sex = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"PhotoFilename") == 0)
                student->PhotoFilename = GetStringContent(pXmlReader);

            else if (wcscmp(pName, L"GradePointAverage") == 0)
                student->GradePointAverage = GetDoubleContent(pXmlReader);

            else
                GetStringContent(pXmlReader);
        }
        else if (xmlNodeType == XmlNodeType_EndElement)
        {
            break;
        }
    }
    return student;
}

LPCWSTR StudentBodyPresenter::GetLocalName(ComPtr<IXmlReader> pXmlReader)
{
    LPCWSTR pName = nullptr;
    unsigned int charCount = 0;
    HRESULT hr = pXmlReader->GetLocalName(&pName, &charCount);

    if (FAILED(hr))
        throw ref new COMException(hr, "XmlReader->GetLocalName failure");

    return pName;
}

String^ StudentBodyPresenter::GetStringContent(ComPtr<IXmlReader> pXmlReader)
{
    String^ string = ref new String();

    if (!pXmlReader->IsEmptyElement())
    {
        XmlNodeType xmlNodeType;
        while (S_OK == pXmlReader->Read(&xmlNodeType))
        {
            if (xmlNodeType == XmlNodeType_Text)
            {
                LPCWSTR pValue = nullptr;
                unsigned int charCount = 0;
                HRESULT hr = pXmlReader->GetValue(&pValue, &charCount);

                if (FAILED(hr))
                    throw ref new COMException(hr, "XmlReader->GetValue failure");

                string = ref new String(pValue);
            }
            else if (xmlNodeType == XmlNodeType_EndElement)
            {
                break;
            }
        }
    }
    return string;
}

double StudentBodyPresenter::GetDoubleContent(ComPtr<IXmlReader> pXmlReader)
{
    return _wtof(GetStringContent(pXmlReader)->Data());
}

// Mimic changing grade point averages
void StudentBodyPresenter::OnTimerTick(Object^ sender, Object^ args)
{
    int index = rand();
    index %= this->StudentBody->Students->Size;
    Student^ student = this->StudentBody->Students->GetAt(index);
    double factor = 1 + (rand() / (double)RAND_MAX - 0.5) / 5;
    student->GradePointAverage = max(0.0, min(5.0, (int)(100 * factor * student->GradePointAverage) / 100.0));
}


