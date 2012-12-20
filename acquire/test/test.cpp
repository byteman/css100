#include <cstdio>
#include "acquire.h"
#include <Poco/Thread.h>

class AcqireTest:public CollectorNotify
{
public:
    void notify(TAdParam* ad_param, TRunParam* run_param)
    {
        printf("angle_ad=%0.2f\n",ad_param->ad_horizontal_arm_angle);
        printf("angle_value=%0.2f\n",run_param->horizontal_arm_angle);
    }
};
int main()
{
    AcqireTest test;
    Collector::get ().start ("/dev/ttyUSB0","/dev/ttyUSB1");
    Collector::get ().addObserver (&test);

    while(1)
    {
        Poco::Thread::sleep (1000);
    }
    return 0;
}

