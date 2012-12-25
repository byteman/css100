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
/*!
保护区域信息
*/
struct TProtectedArea{

};
#endif
