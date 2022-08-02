

struct X
{
    static const int    x   =   10;
};

struct Y
{
    static const double y   =   10.1010;
};

int main()
{
    return X::x + (int)Y::y;
}
