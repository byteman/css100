#include <cstdio>
#include <vector>
#include <Poco/Runnable.h>
#include <Poco/ThreadPool.h>
#include <Poco/SingletonHolder.h>
#include <Poco/NumberParser.h>
#include <math.h>
#include "dataacquire.h"
#include "filter.h"



using Poco::Runnable;
using Poco::SingletonHolder;

//std::string pathToMcu       = "/dev/ttyUSB0";
//std::string pathToEncoder   = "/dev/ttyUSB1";
std::string pathToMcu       = "/dev/pts/1";
std::string pathToEncoder   = "/dev/pts/6";
unsigned char encoderAddr   =  0;
CDataAcquire::CDataAcquire():
    m_observer(NULL)
{

}
CDataAcquire& CDataAcquire::get()
{
    static SingletonHolder<CDataAcquire> sh;
    return *sh.get();
}
void CDataAcquire::onNotify(int type,TAdParam* ad)
{
    #if 1
    m_normalizer.calc (type,ad);
    if(m_observer)
    {
        m_observer->notify (m_normalizer.getRunTimeParam ());
    }
    #endif
}

bool CDataAcquire::start(TCraneBaseInfo *info)
{
    if(info==NULL) return false;
    if(!m_normalizer.initParam (info))
    {
        printf("m_normalizer init failed\n");
        return false;
    }

    m_adc.registerObserver (this);
    if(!m_adc.startAll (pathToMcu,pathToEncoder,encoderAddr))
    {
        return false;
    }
    return true;
}
TQuantizationParam* CDataAcquire::getQuantizaterValue()
{
    return NULL;
}

TRunParam* CDataAcquire::getNormalizerValue()
{
    return &(m_normalizer.m_rtParam);
}
void CDataAcquire::addObserver( CollectorNotify*     observer)
{
    m_observer = observer;
}
void CDataAcquire::removeObserver( CollectorNotify*  observer)
{

}

bool CDataAcquire::stop()
{
    return false;
}
bool CDataAcquire::pause(bool yes)
{
    return false;
}
struct TCalibrateProcess{
    int step;
    TCalibrateParam calib_param;
};
TCalibrateProcess calProcess[CAL_MAX];

int CDataAcquire::getCurAD(EnumCalibType type)
{
    int ad = 0;
    TAdParam* var = m_adc.getAdParam ();
    switch(type)
    {
        case CAL_DG_HEIGHT:
            ad = var->ad_dg_height;
            break;
        case CAL_DG_WEIGHT:
        case CAL_DG_WEIGHT2:
        case CAL_DG_WEIGHT3:
            ad = var->ad_dg_weight;
            break;
        case CAL_HOR_ARM_ANGLE:
            ad = var->ad_horizontal_arm_angle;
            break;
        case CAL_MOTIVE_ARM_ANGLE:
            ad = var->ad_motive_arm_angle;
            break;
        case CAL_POSITON:
            ad = var->ad_position;
            break;
        default:
            break;
    }
    return ad;
}
int  CDataAcquire::calibrateZero(EnumCalibType type, double value)
{
    calProcess[type].calib_param.calibrate_point.ad_zero    = getCurAD(type);
    calProcess[type].calib_param.calibrate_point.value_zero = value;
    calProcess[type].calib_param.calibrate_type = type;
    calProcess[type].step = 1;
    return 1;
}
int  CDataAcquire::calibrateValue(EnumCalibType type,double value)
{
    if(calProcess[type].step == 1)
    {
        int ad   = getCurAD(type);
        int zero = calProcess[type].calib_param.calibrate_point.ad_zero;
        double zero_value = calProcess[type].calib_param.calibrate_point.value_zero;
        calProcess[type].calib_param.calibrate_point.ad_calib_point    = ad;
        calProcess[type].calib_param.calibrate_point.value_calib_point = value;
        double k = (ad - zero) / (value-zero_value);
        calProcess[type].calib_param.calibrate_k = k;
        calProcess[type].step++;
        return calProcess[type].step;
    }
    return -1;
}
bool CDataAcquire::calibrateSave(EnumCalibType type)
{
    if(calProcess[type].step == 2)
    {
        m_normalizer.saveParam (type,&(calProcess[type].calib_param));
        calProcess[type].step = 0;
        return true;
    }
    return false;
}
