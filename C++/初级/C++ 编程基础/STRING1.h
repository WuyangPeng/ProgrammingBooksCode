class string
{
public:
    string();
    string(const string& Str);
    string& operator = (const string& Str);
    ~string();

    string(char* p);

private:
    short m_Length;
    char* m_Data;
};
