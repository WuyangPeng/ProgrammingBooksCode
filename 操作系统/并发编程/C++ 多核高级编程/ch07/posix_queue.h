
//Listing 7-3

  #ifndef __POSIX_QUEUE
  #define __POSIX_QUEUE
  using namespace std;
  #include <string>
  #include <mqueue.h>
  #include <errno.h>
  #include <iostream>
  #include <sstream>
  #include <sys/stat.h>


  class posix_queue{
  protected:
     mqd_t  PosixQueue;
     mode_t  OMode;
     int   QueueFlags;
     string QueueName;
     struct mq_attr  QueueAttr;
     int  QueuePriority;
     int MaximumNoMessages;
     int MessageSize;
     int ReceivedBytes;
     void setQueueAttr(void);
  public:
     posix_queue(void);
     posix_queue(string QName);
     posix_queue(string QName,int MaxMsg, int MsgSize);
     ~posix_queue(void);
    
     mode_t  openMode(void);
     void openMode(mode_t OPmode);
    
     int queueFlags(void);
     void queueFlags(int X);
    
     int queuePriority(void);
     void queuePriority(int X);
    
     int maxMessages(void);
     void maxMessages(int X);
     int messageSize(void);
     void messageSize(int X);
    
     void queueName(string X);
     string queueName(void);
    
     bool open(void);
     int send(string Msg);
     int receive(string &Msg);
     int remove(void);
     int close(void);
    

  };



#endif
