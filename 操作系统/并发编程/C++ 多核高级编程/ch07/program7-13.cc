
//Listing 7-13

  using namespace std;
  #include <iostream>
  #include <pthread.h>

  int Number;
  pthread_t ThreadA,ThreadB;
  pthread_mutex_t Mutex,EventMutex;
  pthread_cond_t Event;

  void *worker1(void *X)
  {
     for(int Count = 1;Count < 10;Count++){
        pthread_mutex_lock(&Mutex);
        Number++;
        pthread_mutex_unlock(&Mutex);
        cout << "worker1: Number = " << Number << endl;
        if(Number == 7){
           pthread_cond_signal(&Event);
        }
     }
   
     return(0);
  }

  void *worker2(void *X)
  {
     pthread_mutex_lock(&EventMutex);
     pthread_cond_wait(&Event,&EventMutex);
     pthread_mutex_unlock(&EventMutex);
     for(int Count = 1;Count < 10;Count++){
        pthread_mutex_lock(&Mutex);
        Number = Number + 20;
        cout << "worker2: Number = " << Number << endl;
        pthread_mutex_unlock(&Mutex);
      
     }
   
     return(0);
  }


  int main(int argc, char *argv[])
  {
     pthread_mutex_init(&Mutex,NULL);
     pthread_mutex_init(&EventMutex,NULL);
     pthread_cond_init(&Event,NULL);
     pthread_create(&ThreadA,NULL,worker1,NULL);
     pthread_create(&ThreadB,NULL,worker2,NULL);
   
     pthread_join(ThreadA,NULL);
     pthread_join(ThreadB,NULL);
   
     return (0);
  }

