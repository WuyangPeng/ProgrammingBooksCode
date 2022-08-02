class string
{
public:
    string(const string& Str);
    string(char* p);
    string& operator=(const string& Str);
    ~string();
private:
    string();
    short m_Length;
    char* m_Data;
};

int main()
{
    string s("Test");
    string n;

    n = s;

    return 0;
}
