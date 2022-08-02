class string
{
public:
    string();
    string(const string& Str);
    string(char* p);
    string& operator = (const string& Str);
    ~string();
private:
    short m_Length;
    char* m_Data;
};

int main()
{
    string s;
    string n("Test");
    string x;
    short Length;

    Length = n.m_Length;

    s = n;
    n = "My name is Susan";

    x = n;
    return 0;
}
