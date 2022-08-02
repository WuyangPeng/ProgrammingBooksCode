#include <string.h>
#include "eclasses.h"



general_exception::general_exception(void)
{
   strcpy(Operation,"");
   strcpy(Message,"Exception Encountered");
}

general_exception::general_exception(char *Msg)
{
   strcpy(Message,Msg);
   strcpy(Operation,"");
}

general_exception::general_exception(const general_exception &N)
{
    strcpy(Operation,N.Operation);
    strcpy(Message,N.Message);
}

general_exception &general_exception::operator=(const general_exception &N)
{

    strcpy(Operation,N.Operation);
    strcpy(Message,N.Message);
    return(*this);
}
void general_exception::operation(char *Op)
{
    strcpy(Operation,Op);
}

char *general_exception::operation(void)
{

    return(Operation);
}


void general_exception::message(char *Msg)
{
    strcpy(Message,Msg);
}

char *general_exception::message(void)
{
    return(Message);
}

