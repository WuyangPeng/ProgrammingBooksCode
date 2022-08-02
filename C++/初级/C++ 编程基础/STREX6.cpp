class string
{
public:
    string();
    string& operator = (const string& Str);
private:
    string(char* p);
    short m_Length;
    char* m_Data;
};

int main()
{
    string n;

    n = "My name is Susan";

    return 0;
}
