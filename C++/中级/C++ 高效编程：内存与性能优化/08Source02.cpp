#include  <iostream.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "BookTools.h"

#ifdef __cplusplus
}
#endif

//--- Class defs.
class TestClass1
{
public:
        int onlyinbase(int a) {return a;}
        virtual int testvirtualmember(int a ){return 156;};
};


class DerivedTestClass: public TestClass1
{
public:
        int testmember(int a){return a;};
        int testextrapar(int a, int b ){return a;};     
        virtual int testvirtualmember(int a ){return a;};
};


int testglobal(int a ){return a;};

DerivedTestClass derivedclass;

long onlybase()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                derivedclass.onlyinbase(1);
    }
    return 0;
}


long member()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                derivedclass.testmember(1);
    }
    return 0;
}

long vmember()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                derivedclass.testvirtualmember(1);
    }
    return 0;
}


long global()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                testglobal(1);
    }
    return 0;
}

long extrapar()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                derivedclass.testextrapar(1,4); 
    }
    return 0;
}

DerivedTestClass *p;
long ptrmember()
{
        int i;
    for (i = 0 ; i < 100000000; i++)
    {
                p->testmember(1);       
    }
    return 0;
}


void main(void)
{
        p = new DerivedTestClass;
        for(;;)
        {
                cout << "Member   : "<< time_fn(member) << " msec" << endl;
                cout << "VMember  : "<< time_fn(vmember)    << " msec" << endl;
                cout << "Mem+par  : "<< time_fn(extrapar)  << " msec" << endl;
                cout << "basemem  : "<< time_fn(onlybase)  << " msec" << endl;
                cout << "ptrmemb  : "<< time_fn(ptrmember)  << " msec" << endl;
                cout << "Global   : "<< time_fn(global)  << " msec" << endl;
        }

}