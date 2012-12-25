#ifndef NORMALIZECONFIG_H
#define NORMALIZECONFIG_H
#include "acquire.h"
class TByConfigMgr;
class TNormalizeConfig
{
public:
    TNormalizeConfig();
    bool load(TCalibrateParam param[],int size=CAL_MAX);
    bool save(TCalibrateParam param[],int size=CAL_MAX);
    bool saveParam(EnumCalibType type,TCalibrateParam* val);
    bool loadParam(EnumCalibType type,TCalibrateParam* val);
private:

    bool loadWeightParam();
};

#endif // NORMALIZECONFIG_H
