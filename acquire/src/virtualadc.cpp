#include "virtualadc.h"
#include <cstdio>
#include <vector>
#include <Poco/Runnable.h>
#include <Poco/ThreadPool.h>
#include <Poco/SingletonHolder.h>
#include <Poco/NumberParser.h>
#include <Poco/ThreadPool.h>
#include <Poco/Net/Socket.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/NetworkInterface.h>
#include "netutils.h"
static TAdParam            g_AdParam;
static TQuantizationParam  g_QuanParam;
using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::Net::NetworkInterface;
static DatagramSocket adc_socket;
static SocketAddress  adc_address;
static unsigned char  adc_buf[1024];
static CFilter         m_filter[6];

#define ADC_DEBUG
#ifdef ADC_DEBUG
#define ADC_DBG(fmt...) fprintf(stderr,fmt);
#else
#define ADC_DBG(fmt...) do { } while (0)
#endif

#define ADC_PRO_LEN           (18)

VirtualAdc& VirtualAdc::get()
{
    static Poco::SingletonHolder<VirtualAdc> sh;
    return *sh.get();
}

VirtualAdc::VirtualAdc()
{
    m_observer = NULL;
}
void VirtualAdc::calc_rt_value(unsigned char data[],size_t len)
{
    printf("calc_rt_value\n");
#ifdef ADC_DEBUG
    ADC_DBG("ad1 data=");
    for(size_t i=0; i < len; i++)
    {
        ADC_DBG("0x%x ",data[i]);
    }
    fprintf(stderr,"\n");
#endif
    if(len != ADC_PRO_LEN) return;
    if( (data[0] == 0xaa) && (data[ADC_PRO_LEN-1] == 0x55) )
    {
         static int wild_cnt  = 0;
         g_AdParam.ad_position  = m_filter[0].Filter ((data[1]<<8)+data[2]);
         g_AdParam.ad_dg_height = m_filter[1].Filter ((data[3]<<8)+data[4]);
         g_AdParam.ad_dg_weight = m_filter[2].Filter ((data[5]<<8)+data[6]);
         g_AdParam.ad_crane_inclined_angle_x = m_filter[4].Filter ((data[7]<<8)+data[8]);
         g_AdParam.ad_crane_inclined_angle_y = m_filter[5].Filter ((data[9]<<8)+data[10]);
         g_AdParam.ad_horizontal_arm_angle = (data[11]<<24)+(data[12]<<16)+(data[13]<<8)+(data[14]);

         if(data[15]&0x80)
         {
             wild_cnt++;
             if(wild_cnt > 30)
             {
                 g_AdParam.ad_wind_speed = 0;
                 wild_cnt = 0;
             }

         }else{
             wild_cnt = 0;
             int ad_wild_speed =  (data[15]<<8)+data[16];
             ad_wild_speed &= 0x7FFF;
             g_AdParam.ad_wind_speed = ad_wild_speed;

         }

         if(m_observer)
         {
             m_observer->onNotify (0,&g_AdParam);
             m_observer->onNotify (1,&g_AdParam);
         }


    }
}

void VirtualAdc::run()
{

    adc_address = SocketAddress(NetAddress::getInterfaceAddr("eth0"),5555);
    adc_socket.bind (adc_address,true);
    while(1)
    {
        ADC_DBG("ready receive....\n");
        int len = adc_socket.receiveBytes (adc_buf,1024);
        ADC_DBG("got[%d]....\n",len);
        if(len >= ADC_PRO_LEN)
            calc_rt_value(adc_buf,len);
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
