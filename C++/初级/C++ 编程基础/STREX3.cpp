class string
{
public:
    string();
    string(const string& Str);
    string(char* p);
    string& operator=(const string& Str);
private:
    ~string();
    short m_Length;
    char* m_Data;
};

int main()
{
    string s("Test");

    return 0;
}
