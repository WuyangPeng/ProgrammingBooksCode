#include "rational.h"
#include "ctmutex.h"

class mt_rational : public rational{
protected:
    mutex Mutex;
public:
    mt_rational(long Num = 0,long Den= 1);
    mt_rational(const mt_rational &X);
    mt_rational &operator=(const mt_rational &X);
    void assign(long X, long Y);
};

