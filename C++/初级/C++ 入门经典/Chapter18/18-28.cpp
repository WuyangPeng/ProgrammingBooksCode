#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

class Runnable
{
 public:
  Runnable();
  Runnable(int *target, int *results, int num, int start, int end);
  void operator()();
 private:
  int *target, *results;
  int num, start, end;
};

Runnable::Runnable()
{
 target=nullptr;
 results=nullptr;
 num=0;
 start=0;
 end=0;
}

Runnable::Runnable(int *target, int *results, int num, int start,
 int end)
{
  this->target= target;
  this->results = results;
  this->num = num;
  this->start = start;
  this->end = end;
}

void Runnable::operator()()
{
 int min = target[start];
 for (int i=start+1; i<=end; i++)
 {
        if (target[i]<min)
                min = target[i];
 }
 results[num] = min;
}

int main()
{
   thread tarr[3];
   int target[] = {31, 66, 41, 8, 92, 47, 22, 87, 45, 92, 4, 14};
   int results[] = {999, 999, 999, 999};
   for (int i = 0; i < 3; i++)
   {
        Runnable r(target, results, i, i*4, i*4+3);
        tarr[i] = thread(r);
   }
   for (int i =0; i < 3; i++)
        tarr[i].join();
   for (int i =0; i < 3; i++)
        cout << results[i] << endl;
   int min = results[0];
   if (min > results[1])
        min = results[1];
   if (min > results[2])
        min = results[2];
   cout << "The minimum from threaded min-search is " << min << endl;
}
