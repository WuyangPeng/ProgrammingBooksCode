
namespace Test1
{
    void Foo(void);
    void Bar(void);

    // ...

    enum eFunction
    {
        FUNCTION_FOO,
        FUNCTION_BAR,
        // ...
    };

    struct Function
    {
        typedef void (*Proc)(void);

        const char* m_Name;
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