#include <Poco/SingletonHolder.h>
#include "acquire.h"
#include "dataacquire.h"
#include "acquiremgr.h"
Collector::Collector()
{

}
Collector& Collector::get()
{
    static Poco::SingletonHolder<Collector> sh;
    return *sh.get();
}
bool Collector::start()
{
    if(AcquireMgr::get ().start ()==false) return false;
    return CDataAcquire::get ().start();
}

bool Collector::stop()
{
    return CDataAcquire::get ().stop ();
}
bool Collector::pause(bool yes)
{
    return CDataAcquire::get ().pause (yes);
}

void Collector::addObserver(CollectorNotify*     observer)
{
    return CDataAcquire::get ().addObserver (observer);
}
void Collector::removeObserver(CollectorNotify*  observer)
{
    return CDataAcquire::get ().removeObserver (observer);
}
int  Collector::calibrateZero(EnumCalibType type, double value)
{
    return CDataAcquire::get ().calibrateZero (type,value);
}
bool Collector::calibrateSave(EnumCalibType type)
{
    return CDataAcquire::get ().calibrateSave (type);
}
int  Collector::calibrateValue(EnumCalibType type,double value)
{
    return CDataAcquire::get ().calibrateValue (type,value);
}
int  Collector::calibrateEnable(EnumCalibType type,bool enable)
{

}
TQuantizationParam* Collector::getQuantizaterValue()
{
    return CDataAcquire::get ().getQuantizaterValue ();
}
TRunParam* Collector::getNormalizerValue()
{
    return CDataAcquire::get ().getNormalizerValue ();
}
