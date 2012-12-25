#include "normalizeconfig.h"
#include "ByConfigMgr.h"
#include <map>
#define PATH_CONFIG        "calbirate.db"
#define SECTION_HEIGHT    "tbl_height"
#define SECTION_WEIGHT    "tbl_weight"
#define SECTION_WEIGHT2   "tbl_weight2"
#define SECTION_WEIGHT3   "tbl_weight3"
#define SECTION_ANGLE     "tbl_angle"
#define SECTION_POSTION   "tbl_postion"
#define SECTION_UP_ANGLE  "tbl_up_angle"
#define KEY_ENABLE        "enable"
#define KEY_K             "k"
#define KEY_AD_ZERO       "ad_zero"
#define KEY_AD_CALIB      "ad_calibrate"
#define KEY_VALUE_CALIB   "value_calibrate"
#define KEY_VALUE_ZERO    "value_zero"

typedef std::map<EnumCalibType,std::string> TCalibTypeMap;

static TCalibTypeMap calibTypeMaps;
TNormalizeConfig::TNormalizeConfig()
{
    calibTypeMaps[CAL_DG_HEIGHT] = SECTION_HEIGHT;
    calibTypeMaps[CAL_DG_WEIGHT] = SECTION_WEIGHT;
    calibTypeMaps[CAL_DG_WEIGHT2] = SECTION_WEIGHT2;
    calibTypeMaps[CAL_DG_WEIGHT3] = SECTION_WEIGHT3;
    calibTypeMaps[CAL_HOR_ARM_ANGLE] = SECTION_ANGLE;
    calibTypeMaps[CAL_MOTIVE_ARM_ANGLE] = SECTION_UP_ANGLE;
    calibTypeMaps[CAL_POSITON] = SECTION_UP_ANGLE;

}
bool TNormalizeConfig::load(TCalibrateParam param[],int size)
{


    loadParam(CAL_DG_HEIGHT,&param[CAL_DG_HEIGHT]);
    loadParam(CAL_POSITON,&param[CAL_POSITON]);
    loadParam(CAL_DG_WEIGHT,&param[CAL_DG_WEIGHT]);
    loadParam(CAL_DG_WEIGHT2,&param[CAL_DG_WEIGHT2]);
    loadParam(CAL_DG_WEIGHT3,&param[CAL_DG_WEIGHT3]);
    loadParam(CAL_MOTIVE_ARM_ANGLE,&param[CAL_MOTIVE_ARM_ANGLE]);
    loadParam(CAL_HOR_ARM_ANGLE,&param[CAL_HOR_ARM_ANGLE]);
#if 0
    param[CAL_DG_HEIGHT].calibrate_type = CAL_DG_HEIGHT;
    param[CAL_DG_HEIGHT].calibrate_enable        = config.ReadBool (SECTION_HEIGHT,KEY_ENABLE,false);
    param[CAL_DG_HEIGHT].calibrate_point.ad_zero = config.ReadInteger (SECTION_HEIGHT,KEY_AD_ZERO,0);
    param[CAL_DG_HEIGHT].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_HEIGHT,KEY_AD_CALIB,0);
    param[CAL_DG_HEIGHT].calibrate_point.value_zero = config.ReadInteger (SECTION_HEIGHT,KEY_VALUE_ZERO,0);
    param[CAL_DG_HEIGHT].calibrate_point.value_calib_point = config.ReadInteger (SECTION_HEIGHT,KEY_VALUE_CALIB,0);
    param[CAL_DG_HEIGHT].calibrate_k = config.ReadFloat (SECTION_HEIGHT,KEY_K,1);


    param[CAL_POSITON].calibrate_type = CAL_POSITON;
    param[CAL_POSITON].calibrate_enable        = config.ReadBool (SECTION_POSTION,KEY_ENABLE,false);
    param[CAL_POSITON].calibrate_point.ad_zero = config.ReadInteger (SECTION_POSTION,KEY_AD_ZERO,0);
    param[CAL_POSITON].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_POSTION,KEY_AD_CALIB,0);
    param[CAL_POSITON].calibrate_point.value_zero = config.ReadInteger (SECTION_POSTION,KEY_VALUE_ZERO,0);
    param[CAL_POSITON].calibrate_point.value_calib_point = config.ReadInteger (SECTION_POSTION,KEY_VALUE_CALIB,0);
    param[CAL_POSITON].calibrate_k = config.ReadFloat (SECTION_POSTION,KEY_K,1);


    param[CAL_DG_WEIGHT].calibrate_type = CAL_DG_WEIGHT;
    param[CAL_DG_WEIGHT].calibrate_enable        = config.ReadBool (SECTION_WEGIHT,KEY_ENABLE,false);
    param[CAL_DG_WEIGHT].calibrate_point.ad_zero = config.ReadInteger (SECTION_WEGIHT,KEY_AD_ZERO,0);
    param[CAL_DG_WEIGHT].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_WEGIHT,KEY_AD_CALIB,0);
    param[CAL_DG_WEIGHT].calibrate_point.value_zero = config.ReadInteger (SECTION_WEGIHT,KEY_VALUE_ZERO,0);
    param[CAL_DG_WEIGHT].calibrate_point.value_calib_point = config.ReadInteger (SECTION_WEGIHT,KEY_VALUE_CALIB,0);
    param[CAL_DG_WEIGHT].calibrate_k = config.ReadFloat (SECTION_WEGIHT,KEY_K,1);


    param[CAL_DG_WEIGHT2].calibrate_type = CAL_DG_WEIGHT2;
    param[CAL_DG_WEIGHT2].calibrate_enable        = config.ReadBool (SECTION_WEGIHT2,KEY_ENABLE,false);
    param[CAL_DG_WEIGHT2].calibrate_point.ad_zero = config.ReadInteger (SECTION_WEGIHT2,KEY_AD_ZERO,0);
    param[CAL_DG_WEIGHT2].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_WEGIHT2,KEY_AD_CALIB,0);
    param[CAL_DG_WEIGHT2].calibrate_point.value_zero = config.ReadInteger (SECTION_WEGIHT2,KEY_VALUE_ZERO,0);
    param[CAL_DG_WEIGHT2].calibrate_point.value_calib_point = config.ReadInteger (SECTION_WEGIHT2,KEY_VALUE_CALIB,0);
    param[CAL_DG_WEIGHT2].calibrate_k = config.ReadFloat (SECTION_WEGIHT2,KEY_K,1);


    param[CAL_DG_WEIGHT3].calibrate_type = CAL_DG_WEIGHT3;
    param[CAL_DG_WEIGHT3].calibrate_enable        = config.ReadBool (SECTION_WEGIHT3,KEY_ENABLE,false);
    param[CAL_DG_WEIGHT3].calibrate_point.ad_zero = config.ReadInteger (SECTION_WEGIHT3,KEY_AD_ZERO,0);
    param[CAL_DG_WEIGHT3].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_WEGIHT3,KEY_AD_CALIB,0);
    param[CAL_DG_WEIGHT3].calibrate_point.value_zero = config.ReadInteger (SECTION_WEGIHT3,KEY_VALUE_ZERO,0);
    param[CAL_DG_WEIGHT3].calibrate_point.value_calib_point = config.ReadInteger (SECTION_WEGIHT3,KEY_VALUE_CALIB,0);
    param[CAL_DG_WEIGHT3].calibrate_k = config.ReadFloat (SECTION_WEGIHT3,KEY_K,1);

    param[CAL_MOTIVE_ARM_ANGLE].calibrate_type = CAL_MOTIVE_ARM_ANGLE;
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_enable        = config.ReadBool (SECTION_UP_ANGLE,KEY_ENABLE,false);
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_point.ad_zero = config.ReadInteger (SECTION_UP_ANGLE,KEY_AD_ZERO,0);
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_UP_ANGLE,KEY_AD_CALIB,0);
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_point.value_zero = config.ReadInteger (SECTION_UP_ANGLE,KEY_VALUE_ZERO,0);
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_point.value_calib_point = config.ReadInteger (SECTION_UP_ANGLE,KEY_VALUE_CALIB,0);
    param[CAL_MOTIVE_ARM_ANGLE].calibrate_k = config.ReadFloat (SECTION_UP_ANGLE,KEY_K,1);

    param[CAL_HOR_ARM_ANGLE].calibrate_type = CAL_HOR_ARM_ANGLE;
    param[CAL_HOR_ARM_ANGLE].calibrate_enable        = config.ReadBool (SECTION_ANGLE,KEY_ENABLE,false);
    param[CAL_HOR_ARM_ANGLE].calibrate_point.ad_zero = config.ReadInteger (SECTION_ANGLE,KEY_AD_ZERO,0);
    param[CAL_HOR_ARM_ANGLE].calibrate_point.ad_calib_point = config.ReadInteger (SECTION_ANGLE,KEY_AD_CALIB,0);
    param[CAL_HOR_ARM_ANGLE].calibrate_point.value_zero = config.ReadInteger (SECTION_ANGLE,KEY_VALUE_ZERO,0);
    param[CAL_HOR_ARM_ANGLE].calibrate_point.value_calib_point = config.ReadInteger (SECTION_ANGLE,KEY_VALUE_CALIB,0);
    param[CAL_HOR_ARM_ANGLE].calibrate_k = config.ReadFloat (SECTION_ANGLE,KEY_K,1);
#endif

    return true;
}
bool TNormalizeConfig::save(TCalibrateParam param[],int size)
{
    saveParam(CAL_DG_HEIGHT,&param[CAL_DG_HEIGHT]);
    saveParam(CAL_POSITON,&param[CAL_POSITON]);
    saveParam(CAL_DG_WEIGHT,&param[CAL_DG_WEIGHT]);
    saveParam(CAL_DG_WEIGHT2,&param[CAL_DG_WEIGHT2]);
    saveParam(CAL_DG_WEIGHT3,&param[CAL_DG_WEIGHT3]);
    saveParam(CAL_MOTIVE_ARM_ANGLE,&param[CAL_MOTIVE_ARM_ANGLE]);
    saveParam(CAL_HOR_ARM_ANGLE,&param[CAL_HOR_ARM_ANGLE]);
    return true;
}
bool TNormalizeConfig::saveParam(EnumCalibType type,TCalibrateParam* val)
{
    ByConfigMgr config("sqlite3");
    config.Open (PATH_CONFIG);
    std::string section = calibTypeMaps[type];

    config.WriteBool (section,KEY_ENABLE,val->calibrate_type);
    config.WriteInteger (section,KEY_AD_ZERO,val->calibrate_point.ad_zero);
    config.WriteInteger (section,KEY_AD_CALIB,val->calibrate_point.ad_calib_point);
    config.WriteInteger (section,KEY_VALUE_ZERO,val->calibrate_point.value_zero);
    config.ReadInteger (section,KEY_VALUE_CALIB,val->calibrate_point.value_calib_point);
    config.ReadFloat (section,KEY_K,val->calibrate_k);

    config.Close ();
    return true;
}
bool TNormalizeConfig::loadParam(EnumCalibType type,TCalibrateParam* val)
{
    ByConfigMgr config("sqlite3");
    config.Open (PATH_CONFIG);
    std::string section = calibTypeMaps[type];
    val->calibrate_type = type;
    val->calibrate_enable        = config.ReadBool (section,KEY_ENABLE,false);
    val->calibrate_point.ad_zero = config.ReadInteger (section,KEY_AD_ZERO,0);
    val->calibrate_point.ad_calib_point = config.ReadInteger (section,KEY_AD_CALIB,0);
    val->calibrate_point.value_zero = config.ReadInteger (section,KEY_VALUE_ZERO,0);
    val->calibrate_point.value_calib_point = config.ReadInteger (section,KEY_VALUE_CALIB,0);
    val->calibrate_k = config.ReadFloat (section,KEY_K,1);
    config.Close ();
    return true;
}
