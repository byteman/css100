#include <cstdio>
#include <Poco/Thread.h>
#include "acquire.h"
class AcqireTest:public CollectorNotify
{
public:

    void notify(TRunParam* param)
    {
        printf("weight=%0.2f\n",param->dg_weight);
    }
};
int main()
{
    AcqireTest test;
    Collector::get ().start ();
    Collector::get ().addObserver (&test);

    while(1)
    {
        Poco::Thread::sleep (1000);
    }
    return 0;
}

