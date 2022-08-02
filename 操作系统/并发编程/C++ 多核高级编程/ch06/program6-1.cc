//Listing 6-1



   using namespace std;
      
   #include <iostream>
   #include <pthread.h>
      	
      	
   void *task1(void *X)
   {
      int *Temp;
      Temp = static_cast<int *>(X);
    	
     for(int Count = 0;Count < *Temp;Count++)
     {
         cout << "work from thread: " << Count << endl;
     }
     cout << "Thread complete" << endl;
     return (NULL);
  }
    	


  int main(int argc, char *argv[])
  {
     int N;
   		
     pthread_t MyThreads[10];
   		
     if(argc != 2){
         cout << "error" << endl;
    	   exit (1);
     }
    		
     N = atoi(argv[1]);
    		
     if(N > 10){
         N = 10;
     }
    		
     for(int Count = 0;Count < N;Count++)
     {
         pthread_create(&MyThreads[Count],NULL,task1,&N);
    	   
     }
    		
    		
     for(int Count = 0;Count < N;Count++)
     {
         pthread_join(MyThreads[Count],NULL);
   	   
     }
     return(0);
    		
    		
   } 	


