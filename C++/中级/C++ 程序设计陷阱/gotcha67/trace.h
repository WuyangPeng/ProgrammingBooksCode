#ifndef TRACE_H
#define TRACE_H

#include <iostream>

class Trace {
  public:
    Trace( const char *msg )
        : m_( msg ) { std::cout << "Entering " << m_ << std::endl; }
    ~Trace()
        { std::cout << "Exiting " << m_ << std::endl; }
  private:
    const char *m_;
};

#endif
