

class String
{
public:
    explicit String(char const *s)
        : m_s(s)
    {}
    explicit String(String const &rhs)
        : m_s(rhs.m_s)
    {}

protected:
    char const  *m_s;
};

String MakeString(char const *s)
{
    return String(s);

//  return r_val;
}

int main()
{
    String  s1("Literal");
    String  s2(s1);
    String  s3 = "x";

    String  s4("s3");


    return 0;
}
