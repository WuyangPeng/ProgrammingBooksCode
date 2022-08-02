class string
{
friend std::ostream& operator << (std::ostream& os, const string& Str);
friend std::istream& operator >> (std::istream& is, string& Str);

public:
    string();
    string(const string& Str);
    string& operator = (const string& Str);
    ~string();

    string(char* p);
    short GetLength();
    bool operator < (const string& Str);
    bool operator == (const string& Str);

private:
    short m_Length;
    char* m_Data;
};
