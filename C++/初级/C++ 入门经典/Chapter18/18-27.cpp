#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

class Runnable
{
  public:
    Runnable();
    Runnable(int n);
    void operator()();  // Note the two ()()
  private:
    int num;
};
Runnable::Runnable() : num(0)
{ }
Runnable::Runnable(int n) : num(n)
{ }
void Runnable::operator()()
{
        cout << "Hello world, I am number " << num <<  endl;
}

int main()
{
    Runnable r1(10);
    Runnable r2(20);

    thread t1(r1);
    thread t2(r2);

    t1.join();
    t2.join();
}
