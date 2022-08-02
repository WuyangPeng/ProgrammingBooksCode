#ifndef __GENEXCEP__H
#define __GENEXCEP__H

class general_exception{
protected:
    char Operation[2];
    char Message[81];
public:
    general_exception(void);
    general_exception(char *Msg);
    general_exception(const general_exception &N);
    general_exception &operator=(const general_exception &N);
    void operation(char *Op);
    char *operation(void);
    void message(char *Msg);
    char *message(void);
};
#endif


