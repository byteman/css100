#include <cstdio>
#include <Poco/Thread.h>
#include "acquire.h"

TCraneBaseInfo info;

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
    info.LongArmLength = 100;
    info.Dyna = false;

    if(Collector::get ().start (&info,sizeof(TCraneBaseInfo)))
    {
        printf("start ok\n");
    }
    Collector::get ().addObserver (&test);

    while(1)
    {
        Poco::Thread::sleep (1000);
    }
    return 0;
}

