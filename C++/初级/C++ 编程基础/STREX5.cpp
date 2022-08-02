class string
{
public:
    string(const string& Str);
    string(char* p);
    string& operator = (const string& Str);
    ~string();
private:
    string();
    short m_Length;
    char* m_Data;
};

int main()
{
    string n("Test");
    string x = n;

    n = "My name is Susan";

    return 0;
}
