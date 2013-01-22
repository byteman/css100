#ifndef ACQUIRE_H
#define ACQUIRE_H

#include <iostream>
#include <vector>
#include <string>
#include "css100.h"
struct TCalibratePoint{
    int ad_zero;
    int ad_calib_point;
    double value_calib_point;
    double value_zero;
};
typedef std::vector<TCalibratePoint> TCalibratePointList;
typedef std::vector<double> TCalibrateKList;

enum EnumCalibType{
    CAL_POSITON = 0,  //小车幅度标定
    CAL_DG_HEIGHT,  //小车幅度标定
    CAL_DG_WEIGHT,  //第一段重量标定
    CAL_DG_WEIGHT2, //第二段重量标定
    CAL_DG_WEIGHT3, //第三段重量标定
    CAL_WIND_SPEED, //风速标定
    CAL_MOTIVE_ARM_ANGLE, //仰臂标定
    CAL_HOR_ARM_ANGLE, //平臂标定
    CAL_CRANE_INCANGLE_X,
    CAL_CRANE_INCANGLE_Y,
    CAL_HOR_ARM_INCANGLE_X,
    CAL_HOR_ARM_INCANGLE,
    CAL_MAX
};
struct TCalibrateParam{
    bool                calibrate_enable;
    EnumCalibType       calibrate_type;
    TCalibratePoint     calibrate_point;
    double              calibrate_k;
    //TCalibratePointList calibrate_points;
    //TCalibrateKList     calibrate_ks;
};
struct TQuantizationParam{
    int mv_position;    //小车的幅度
    int mv_dg_height; //吊钩高度
    int mv_dg_weight; //吊钩重量
    int mv_wind_speed; //风速
    int mv_motive_arm_angle; //动臂角度
    int mv_horizontal_arm_angle; //平臂旋转角度
    int mv_crane_inclined_angle_x; //塔身X方向倾斜角度
    int mv_crane_inclined_angle_y; //塔身Y方向倾斜角度
    int mv_horizontal_arm_inclined_angle_x; //平臂X方向倾斜角度
    int mv_horizontal_arm_inclined_angle_y; //平臂Y方向倾斜角度
};
struct TAdParam{
    TAdParam()
    {
        ad_position = 0;
        ad_dg_height = 0;
        ad_dg_weight = 0;
        ad_wind_speed = 0;
        ad_motive_arm_angle = 0;
        ad_horizontal_arm_angle = 0;
        ad_crane_inclined_angle_x = 0;
        ad_crane_inclined_angle_y = 0;
        ad_horizontal_arm_inclined_angle_x = 0;
        ad_horizontal_arm_inclined_angle_y = 0;
    }
    int ad_position;    //小车的幅度
    int ad_dg_height; //吊钩高度
    int ad_dg_weight; //吊钩重量
    int ad_wind_speed; //风速
    int ad_motive_arm_angle; //动臂角度
    int ad_horizontal_arm_angle; //平臂旋转角度
    int ad_crane_inclined_angle_x; //塔身X方向倾斜角度
    int ad_crane_inclined_angle_y; //塔身Y方向倾斜角度
    int ad_horizontal_arm_inclined_angle_x; //平臂X方向倾斜角度
    int ad_horizontal_arm_inclined_angle_y; //平臂Y方向倾斜角度
};

struct TRunParam{
    TRunParam()
    {
        position = 0;
        dg_height = 0;
        dg_weight = 0;
        wind_speed = 0;
        motive_arm_angle = 0;
        horizontal_arm_angle = 0;
        crane_inclined_angle_x = 0;
        crane_inclined_angle_y = 0;
        horizontal_arm_inclined_angle_x = 0;
        horizontal_arm_inclined_angle_y = 0;
    }
    double position;    //小车的幅度
    double dg_height; //吊钩高度
    double dg_weight; //吊钩重量
    double wind_speed; //风速
    double motive_arm_angle; //动臂角度
    double horizontal_arm_angle; //平臂旋转角度
    double crane_inclined_angle_x; //塔身X方向倾斜角度
    double crane_inclined_angle_y; //塔身Y方向倾斜角度
    double horizontal_arm_inclined_angle_x; //平臂X方向倾斜角度
    double horizontal_arm_inclined_angle_y; //平臂Y方向倾斜角度
};

struct CollectorNotify
{
    virtual void notify(TRunParam* param) = 0;
};
typedef struct tag_CraneInfo{
    bool    dynmaic;
    double  long_arm;
}TCraneInfo;
struct Collector
{
    Collector();
    static Collector& get();
/*
为了防止其他模块传入的TCraneBaseInfo的大小和内部使用的不一致
*/
    bool start(TCraneBaseInfo* info,unsigned int sizeofInfo);

    int  calibrateZero(EnumCalibType type, double value);
    int  calibrateValue(EnumCalibType type,double value);
    bool calibrateSave(EnumCalibType type);
    int  calibrateEnable(EnumCalibType type,bool enable);

    bool stop();
    bool pause(bool yes);

    void addObserver(CollectorNotify*     observer);
    void removeObserver(CollectorNotify*  observer);
    TQuantizationParam* getQuantizaterValue();
    TRunParam* getNormalizerValue();
    TCalibrateParam* getCalibrateValue(EnumCalibType type);

};


#endif // ACQUIRE_H
