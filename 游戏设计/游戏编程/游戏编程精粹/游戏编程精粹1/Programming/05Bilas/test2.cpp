#include <string>
#include <vector>

namespace Test2
{
    struct Parameters
    {
        std::vector<unsigned char> m_Data;

        bool ExtractBool(void);
        int ExtractInt(void);
        float ExtractFloat(void);
        const char* ExtractString(void);

        void AddBool(bool);
        void AddInt(int);
        void AddFloat(float);
        void AddString(const char*);
    };

    void Foo(Parameters& params)
    {
        [[maybe_unused]] int param1 = params.ExtractInt();
        [[maybe_unused]] float param2 = params.ExtractFloat();
        //  π”√param1£¨param2°≠°≠
    }

    void Bar(Parameters& params);
    // ...

    enum eFunction
    {
        FUNCTION_FOO,
        FUNCTION_BAR,
    };

    struct Function
    {
        typedef void (*Proc)(Parameters&);

        std::string m_Name;
        Proc m_Proc;
        eFunction m_Function;
    };

    Function g_Fuctions[] = {
        {
            "Foo",
            Foo,
            FUNCTION_FOO,
        },

        {
            "Bar",
            Bar,
            FUNCTION_BAR,
        },
    };

}