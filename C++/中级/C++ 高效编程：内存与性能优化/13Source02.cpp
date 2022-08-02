#include <stdio.h>
#include <unistd.h>
#include <stream.h>
#include <pthread.h>

struct StartInput
{
        char    name[8];
        long     number;
        long     length;
};

void *StartThread(void* startInput)
{
        StartInput *in = (StartInput*) startInput;

        int k = in->number;
        int j = in->length + k;
 
        for(; k < j; k++)
        {
            if ((k % 10000) == 0)
        		cout << k << in->name << endl;
        }

        pthread_exit(NULL);
}


void main(void)
{
        pthread_t  thread1, thread2; // Thread structures.
        StartInput startInputA, startInputB;
        
        strcpy(startInputA.name,"ThreadA");
        strcpy(startInputB.name,"ThreadB");
        startInputA.number = 0;
        startInputB.number = 0;
        startInputA.length = 1000000;
        startInputB.length = 1000000;

        pthread_create(&thread1, NULL, StartThread, (void*) &startInputA);
        pthread_create(&thread2, NULL, StartThread, (void*) &startInputB);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
}
