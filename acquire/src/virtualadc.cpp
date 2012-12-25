#include "virtualadc.h"
#include <cstdio>
#include <vector>
#include <Poco/Runnable.h>
#include <Poco/ThreadPool.h>
#include <Poco/SingletonHolder.h>
#include <Poco/NumberParser.h>
#include <Poco/ThreadPool.h>

static TAdParam            g_AdParam;
static TQuantizationParam  g_QuanParam;

VirtualAdc& VirtualAdc::get()
{
    static Poco::SingletonHolder<VirtualAdc> sh;
    return *sh.get();
}

VirtualAdc::VirtualAdc()
{
    m_observer = NULL;
}
void VirtualAdc::run()
{
    while(1)
    {
        if(m_observer)
        {
            m_observer->onNotify (0,&g_AdParam);
            m_observer->onNotify (1,&g_AdParam);
        }
        Poco::Thread::sleep (100);
    }

}
bool VirtualAdc::startAll(std::string pathToMCU,std::string pathToEncoder,unsigned char encoderAddr)
{
    Poco::ThreadPool::defaultPool ().start (*this);
    return true;
}
bool VirtualAdc::startAcquireMcuAD(std::string pathToMCU)
{
   return true;
}
bool VirtualAdc::startAcquireAngleEncoder(std::string pathToEncoder,unsigned char encoderAddr)
{
   return true;
}

bool VirtualAdc::stop()
{

    return true;
}
bool VirtualAdc::pause(bool yes)
{

}
void VirtualAdc::notify(int type)
{
    if(m_observer)
    {
        m_observer->onNotify (type,&g_AdParam);
    }
}
TQuantizationParam* VirtualAdc::getQuantizationValue()
{
    return &g_QuanParam;
}
TAdParam* VirtualAdc::getAdParam(void)
{
    return &g_AdParam;
}
void VirtualAdc::registerObserver(ADConvertNotify *observer)
{
    m_observer = observer;
}
