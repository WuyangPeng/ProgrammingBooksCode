#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void func(int a)
{
    cout << "Hello World: " << a << " " 
         << std::this_thread::get_id() << endl;
}

int main()
{
    thread t1(func, 10);
    thread t2(func, 20);
    t1.join();
    t2.join();
}
