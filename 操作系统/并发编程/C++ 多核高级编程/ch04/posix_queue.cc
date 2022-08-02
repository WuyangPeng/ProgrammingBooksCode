#include "posix_queue.h"
    
    
posix_queue::posix_queue(void)
{
   
   
   QueueFlags = O_RDWR | O_CREAT | O_EXCL;
   OMode = S_IRUSR | S_IWUSR;
   QueueName.assign("none");
   QueuePriority = 0;
   MaximumNoMessages = 10;
   MessageSize = 8192;
   ReceivedBytes = 0;
   setQueueAttr();
  

}


posix_queue::posix_queue(string QName)
{

   QueueFlags = O_RDWR | O_CREAT | O_EXCL;
   OMode = S_IRUSR | S_IWUSR;
   QueueName.assign(QName);
   QueuePriority = 0;
   MaximumNoMessages = 10;
   MessageSize = 8192;
   ReceivedBytes = 0;
   setQueueAttr();


}
posix_queue::posix_queue(string QName,int MaxMsg, int MsgSize)
{

   QueueFlags = O_RDWR | O_CREAT | O_EXCL;
   OMode = S_IRUSR | S_IWUSR;
   QueueName.assign(QName);
   QueuePriority = 0;
   MaximumNoMessages = MaxMsg;
   MessageSize = MsgSize;
   ReceivedBytes = 0;
   setQueueAttr();
}



posix_queue::~posix_queue(void)
{
    
}    

void posix_queue::setQueueAttr(void)
{


    QueueAttr.mq_maxmsg = MaximumNoMessages;
    QueueAttr.mq_msgsize = MessageSize;

}

mode_t  posix_queue::openMode(void)
{
  return(OMode);
}
void posix_queue::openMode(mode_t OPmode)
{
   OMode = OPmode;
}
int posix_queue::queueFlags(void)
{
   return(QueueFlags);

}
void posix_queue::queueFlags(int X)
{
   QueueFlags = X;
   
}
int posix_queue::queuePriority(void)
{
   return(QueuePriority);

}
void posix_queue::queuePriority(int X)
{
  QueuePriority = X;  
    
}
int posix_queue::maxMessages(void)
{
    return(QueueAttr.mq_maxmsg);
}
void posix_queue::maxMessages(int X)
{
    MaximumNoMessages = X;
    QueueAttr.mq_maxmsg = X;
}
int posix_queue::messageSize(void)
{
    return(QueueAttr.mq_msgsize);
}
void posix_queue::messageSize(int X)
{

   MessageSize = X;
   QueueAttr.mq_msgsize = X;

}
void posix_queue::queueName(string X)
{
   QueueName = X;
  
}
string posix_queue::queueName(void)
{
   return(QueueName);
   
}
bool posix_queue::open(void)
{
  bool Success = true;
  int RetCode;
  PosixQueue = mq_open(QueueName.c_str(),QueueFlags,OMode,&QueueAttr);
  if(errno == EACCES){
    cerr  << "Permission denied to created " << QueueName << endl;
    Success = false;
  }  
  RetCode = mq_getattr(PosixQueue,&QueueAttr);
  if(errno == EBADF){
     cerr << "PosixQueue is not a valid message descriptor" << endl;
     Success = false;     
     close();

  }
  if(RetCode == -1){
       cerr << "unknown error in mq_getattr() " << endl;
       Success = false;
       close();      
  }
  return(Success);
}

int posix_queue::send(string Msg)
{

     int StatusCode = 0;
     if(Msg.size() > QueueAttr.mq_msgsize){
        cerr << "message to be sent is larger than max queue message size " << endl;
	StatusCode = -1;
     }
     StatusCode = mq_send(PosixQueue,Msg.c_str(),Msg.size(),0);
     if(errno == EAGAIN){
        StatusCode = errno;
        cerr << "O_NONBLOCK not set and the queue is full " << endl;               
     }
     if(errno == EBADF){
        StatusCode = errno;
        cerr << "PosixQueue is not a valid descriptor open for writing" << endl;              
     } 
     if(errno == EINVAL){
        StatusCode = errno;
        cerr << "msgprio is out side of the priority range for the message queue or " << endl;
	cerr << "Thread my block causing a timing conflict with time out" << endl;	
     }	
	
     if(errno == EMSGSIZE){
        StatusCode = errno;
        cerr << "message size exceeds maximum size of message parameter on message queue" << endl;
             
     }    
     if (errno == ETIMEDOUT){
         StatusCode = errno;
         cerr << "The O_NONBlock flag was not set, but the time expired before the message " << endl;
	 cerr << "could be added to the queue " << endl;                  
     }
     if(StatusCode == -1){
        cerr << "unknown error in mq_send() " << endl;                
     } 
     return(StatusCode);

}


int posix_queue::receive(string &Msg)
{
   
    int StatusCode = 0;
    char QueueBuffer[QueueAttr.mq_msgsize];
    ReceivedBytes = mq_receive(PosixQueue,QueueBuffer,QueueAttr.mq_msgsize,NULL);    
    if(errno == EAGAIN){
       StatusCode = errno;
       cerr << "O_NONBLOCK not set and the queue is full " << endl;       
       
    }
    if(errno == EBADF){
       StatusCode = errno;
       cerr << "PosixQueue is not a valid descriptor open for writing" << endl;              
    } 
    if(errno == EINVAL){
       StatusCode = errno;
       cerr << "msgprio is out side of the priority range for the message queue or " << endl;
       cerr << "Thread my block causing a timing conflict with time out" << endl;       
    }
    if(errno == EMSGSIZE){
       StatusCode = errno;
       cerr << "message size exceeds maximum size of message parameter on message queue" << endl;      
    }    
    if (errno == ETIMEDOUT){
       StatusCode = errno;
        cerr << "The O_NONBlock flag was not set, but the time expired before the message " << endl;
	cerr << "could be added to the queue " << endl;       
    }
    string XMessage(QueueBuffer,QueueAttr.mq_msgsize);
    Msg = XMessage;	
    return(StatusCode);

}
int  posix_queue::remove(void)
{
    int StatusCode = 0;
    StatusCode = mq_unlink(QueueName.c_str());
    if(StatusCode != 0){
       cerr << "Did not unlink " << QueueName << endl;
    }
    return(StatusCode);   
}

int posix_queue::close(void)
{

   int StatusCode = 0;
   StatusCode = mq_close(PosixQueue);
   if(errno == EBADF){
       StatusCode = errno;
       cerr << "PosixQueue is not a valid descriptor open for writing" << endl;              
   }
   if(StatusCode == -1){
      cerr << "unknown error in mq_close() " << endl;                
   }   
   return(StatusCode);

}



