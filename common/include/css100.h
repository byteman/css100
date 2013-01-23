#ifndef CSS100_H
#define CSS100_H
#include <iostream>
/*!
塔机基础参数
*/
struct TCraneBaseInfo{
    std::string Serial;     //塔机出厂设置的设备序列号
    double   Height;        //塔机高度
    double   X;             //塔机x坐标
    double   Y;             //塔机y坐标
    double   LongArmLength; //大臂长度
    double   ShortArmLenght; //短臂长度
    double   Rs;             //最小幅度
    bool     Dyna;           //是否是动臂式
    double   DLong;          //动臂投影
    double   DHeight;        //动臂高度+吊塔高度
    double   HeatHeight;     //塔帽高度
    double   L1;             //动臂的最大角度85度左右
    double   L2;             //动臂的最小角度15度
    double   a0;             //大臂根部铰点到塔机回转中心的距离，可正或负或0
    double   C2;             //吊点长度
    double   CAng;           //固定夹角
    double   DLine;          //拉绳长度
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

class Crane{
public:
    unsigned int   id;
    TCraneBaseInfo baseInfo;
    TRunParam      runInfo;
};
/*!
保护区域信息
*/
struct TProtectedArea{

};
#endif
