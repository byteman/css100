#include <math.h>
#include <cstdio>
#include <cstring>
#include "normalizer.h"
#include <assert.h>
Normalizer::Normalizer():
    self_crane(NULL)
{
    /*


    //fprintf(stderr,"x=%0.2f y=%0.2f\n",g_angle_x,g_angle_y);

    */
    m_config.load (m_CalParam);
}

void Normalizer::calcAngle(int ad_angle)
{
    static double crane_angle_save,crane_angle,crane_angle_thresh=0;
    TCalibrateParam* pCalPar = &(m_CalParam[CAL_HOR_ARM_ANGLE]);
    crane_angle = (ad_angle - pCalPar->calibrate_point.ad_zero) / pCalPar->calibrate_k
                    + pCalPar->calibrate_point.value_zero;
    if (fabs(crane_angle_save-crane_angle)>crane_angle_thresh)
        crane_angle_save=crane_angle;
    else
        crane_angle=crane_angle_save;
    int int_angle = (int)crane_angle;
    crane_angle=crane_angle-int_angle+(int_angle % 360);
    if (crane_angle<0)
        crane_angle=crane_angle+360;
    m_rtParam.horizontal_arm_angle = crane_angle;

}
bool Normalizer::initParam(Crane* self)
{
    assert(self);
    self_crane = self;
    m_baseInfo = &(self->baseInfo);

    return true;
}
bool Normalizer::saveParam(EnumCalibType type,TCalibrateParam* val)
{
    memcpy(&(m_CalParam[type]),val,sizeof(TCalibrateParam));
    return m_config.saveParam (type,val);
}
bool Normalizer::loadParam(EnumCalibType type,TCalibrateParam* val)
{
    m_config.loadParam (type,val);
    memcpy(&(m_CalParam[type]),val,sizeof(TCalibrateParam));
    return true;
}
double Normalizer::calcvalue(int ad, TCalibrateParam* val)
{
    return (ad - val->calibrate_point.ad_zero) / val->calibrate_k + val->calibrate_point.value_zero;
}
void Normalizer::calcOther(TAdParam  *ad_other)
{
    static double tmp_car_dist  = 0;
    static double tmp_dg_height = 0;
    static double tmp_dg_weight = 0;
////////////////////////////////////////////////////
    TCalibrateParam* val = NULL;
    if(m_baseInfo->Dyna){ //ķŊąÛĘ―ĩÄ·ųķČžÆËã

        ad_other->ad_motive_arm_angle = ad_other->ad_position;
        val = &(m_CalParam[CAL_MOTIVE_ARM_ANGLE]);
        m_rtParam.motive_arm_angle = calcvalue(ad_other->ad_motive_arm_angle,val);

        tmp_car_dist = m_baseInfo->LongArmLength*cos(m_rtParam.motive_arm_angle*3.1415/180) + m_baseInfo->a0;

    }else{ //Æ―ąÛĘ―ĩÄ·ųķČžÆËã
        val = &(m_CalParam[CAL_POSITON]);

        tmp_car_dist = calcvalue(ad_other->ad_position,val);
    }
////////////////////////////////////////////////////
    val = &(m_CalParam[CAL_DG_HEIGHT]);

    tmp_dg_height = calcvalue(ad_other->ad_dg_height,val);

    if(m_baseInfo->Dyna)
    {
        double arm_len = m_baseInfo->LongArmLength;
        double height  = arm_len*sin(ad_other->ad_motive_arm_angle * 3.1415 / 180);
        double zero    = arm_len*sin(15*3.1415/180);

        tmp_dg_height += (height - zero);
    }
////////////////////////////////////////////////////
    val = &(m_CalParam[CAL_DG_WEIGHT]);

    double k = val->calibrate_k;
    double z = val->calibrate_point.ad_zero;

    int    ad_weight = ad_other->ad_dg_weight;

    if( (ad_weight <= m_CalParam[CAL_DG_WEIGHT].calibrate_point.ad_calib_point) && (ad_weight >= m_CalParam[CAL_DG_WEIGHT].calibrate_point.ad_zero))
    {
        k = m_CalParam[CAL_DG_WEIGHT].calibrate_k;
    }
    if( m_CalParam[CAL_DG_WEIGHT2].calibrate_enable && \
              (ad_weight <= m_CalParam[CAL_DG_WEIGHT2].calibrate_point.ad_calib_point) &&  \
              (ad_weight >= m_CalParam[CAL_DG_WEIGHT2].calibrate_point.ad_zero))
    {
        k = m_CalParam[CAL_DG_WEIGHT2].calibrate_k;
    }

    else if( m_CalParam[CAL_DG_WEIGHT3].calibrate_enable && \
              (ad_weight >= m_CalParam[CAL_DG_WEIGHT3].calibrate_point.ad_zero))
    {
        k = m_CalParam[CAL_DG_WEIGHT3].calibrate_k;
    }
    printf("weight_k=%0.2f\n",k);
    tmp_dg_weight=(ad_weight-z)/k;
/////////////////////////////////////////////////////
    m_rtParam.dg_weight = tmp_dg_weight<0?0:tmp_dg_weight;
    m_rtParam.position  = tmp_car_dist<0?0:tmp_car_dist;
    m_rtParam.dg_height = tmp_dg_height;
    m_rtParam.wind_speed   = (double)((ad_other->ad_wind_speed*20)/635); //635 == 20m/s

}
TRunParam* Normalizer::getRunTimeParam()
{
    return &m_rtParam;
}
void Normalizer::calc(int type,TAdParam* adc)
{
    if(type == 1)
    {
        calcAngle(adc->ad_horizontal_arm_angle);
    }
    else if(type == 0)
    {
        calcOther(adc);
    }
}
