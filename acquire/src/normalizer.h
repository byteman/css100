#ifndef NORMALIZER_H
#define NORMALIZER_H

#include "acquire.h"
#include "normalizeconfig.h"
#include "css100.h"
class Normalizer
{
public:
    Normalizer();
    bool initParam(TCraneBaseInfo* baseInfo);
    bool saveParam(EnumCalibType type,TCalibrateParam* val);
    bool loadParam(EnumCalibType type,TCalibrateParam* val);
    bool test(TCraneBaseInfo* baseInfo);
    void calc(int type,TAdParam* adc);
    double calcvalue(int ad, TCalibrateParam* val);
    TRunParam* getRunTimeParam();
    TRunParam        m_rtParam;
    TCalibrateParam  m_CalParam[CAL_MAX];
    TNormalizeConfig m_config;
private:
    void calcAngle(int ad_angle);
    void calcOther(TAdParam  *ad_other);
    TCraneBaseInfo* m_baseInfo;
};

#endif // CALIBRATER_H
