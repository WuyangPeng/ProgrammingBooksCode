class string
{
public:
    string();
    string(const string& Str);
    string& operator = (const string& Str);
    ~string();

    string(char* p);
    void Display();
    short GetLength();

private:
    short m_Length;
    char* m_Data;
};
