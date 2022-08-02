

struct Fatal
{
  Fatal(int i)
    : y(i)
    , x(y * 2)
  {}
  int x;
  int y;
};

int main()
{
    Fatal   f(10);

    return f.x;
}
