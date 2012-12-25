#include "adc.h"

#include <cstdio>
#include <vector>
#include <Poco/Runnable.h>
#include <Poco/ThreadPool.h>
#include <Poco/SingletonHolder.h>
#include <Poco/NumberParser.h>
#include <math.h>
#include "serial/serial.h"


#ifdef ADC_DEBUG
#define ADC_DBG(fmt...) fprintf(stderr,fmt);
#else
#define ADC_DBG(fmt...) do { } while (0)
#endif

#define ADC_PRO_LEN           17

using Poco::Runnable;
using Poco::SingletonHolder;
static TAdParam            g_AdParam;
static TQuantizationParam  g_QuanParam;
class CMcuAcquireWorker:public Poco::Runnable{
public:

    CMcuAcquireWorker(ADConvert* adc,std::string devPath):
         m_adc(adc),
         m_path(devPath)
    {
        m_port.setPort (devPath);
    }
    virtual ~CMcuAcquireWorker()
    {
    }
    virtual bool start(uint32_t baud)
    {
        try{
           m_port.setBaudrate (baud);
           m_port.open ();
        }catch(...){
            fprintf(stderr,"serial %s open failed\n",m_path.c_str());
            return false;
        }
        m_quit = false;
        m_thread.start(*this);
        return m_rdyEvt.tryWait(1000);
    }
    bool stop()
    {
        m_quit = true;
        return m_quitEvt.tryWait(1000);
    }
    void calc_rt_value(unsigned char data[],size_t len)
    {

#ifdef AD_DEBUG
        AD_DBG("ad1 data=");
        for(size_t i=0; i < len; i++)
        {
            AD_DBG("0x%x ",data[i];
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
             g_AdParam.ad_crane_inclined_angle_x = m_filter[4].Filter ((data[9]<<8)+data[10]);
             g_AdParam.ad_crane_inclined_angle_y = m_filter[5].Filter ((data[11]<<8)+data[12]);

             if(data[13]&0x80)
             {
                 wild_cnt++;
                 if(wild_cnt > 30)
                 {
                     g_AdParam.ad_wind_speed = 0;
                     wild_cnt = 0;
                 }

             }else{
                 wild_cnt = 0;
                 int ad_wild_speed =  (data[13]<<8)+data[14];
                 ad_wild_speed &= 0x7FFF;
                 g_AdParam.ad_wind_speed = ad_wild_speed;

             }

             if(m_adc)
             {
                 m_adc->notify (1);
             }


        }
    }
    virtual void run()
    {
        //set_thread_title("ctx2000.ad1");
        m_rdyEvt.set();
        m_quitEvt.reset();
        m_quit = false;
        m_port.setReadTimeout (1000);
        while(!m_quit)
        {
            try
            {
                Poco::Thread::sleep(50);

                m_port.writeByte(0x2);

                size_t len = m_port.read(m_buf,ADC_PRO_LEN);
                if(len >= ADC_PRO_LEN)
                {
                    calc_rt_value(m_buf,ADC_PRO_LEN);
                }
            }
            catch(...)
            {

            }
        }
        m_port.close ();
        m_quitEvt.set();
    }
protected:
    serial::Serial  m_port;
    Poco::Thread    m_thread;
    Poco::Event     m_rdyEvt;
    Poco::Event     m_quitEvt;
    std::string     m_path;
    unsigned char   m_buf[ADC_PRO_LEN+1];
    CFilter         m_filter[6];
    volatile bool   m_quit;
    ADConvert*      m_adc;

};
class CEncoderAcquireWorker:public CMcuAcquireWorker{
public:
    CEncoderAcquireWorker(ADConvert* adc,std::string devpath, char encoder_addr):
        CMcuAcquireWorker(adc,devpath)
    {
        // [ #01 enter ]
        sprintf(m_cmd,"#%02d\r",encoder_addr);
        fprintf(stderr,"cmd=%s",m_cmd);
    }
    virtual ~CEncoderAcquireWorker()
    {

    }
    virtual void run()
    {
        //set_thread_title("ctx2000.ad2");
        m_rdyEvt.set();
        m_quitEvt.reset();
        m_quit = false;

        int tmp=0;
        size_t size = 0;
        m_port.setReadTimeout (100);
        while(!m_quit)
        {
            try
            {
                m_port.flushInput ();
                m_port.write((unsigned char*)m_cmd,4);
                Poco::Thread::sleep(100);
                size = m_port.read ((uint8_t*)m_adBuf,13);
                if(size != 13)
                {
                    continue;
                }
                m_adBuf[12]=0;
                if(Poco::NumberParser::tryParse(m_adBuf+1,tmp))
                {
                    g_AdParam.ad_horizontal_arm_angle = tmp;
                    if(m_adc)
                    {
                        m_adc->notify (0);
                    }
                }
            }
            catch(...)
            {

            }
        }
        m_port.close ();
        m_quitEvt.set();
    }

private:
    char           m_cmd[4];
    char           m_adBuf[15];
    serial::Serial m_port;
    ADConvert*     m_daq;

};


ADConvert& ADConvert::get()
{
    static SingletonHolder<ADConvert> sh;
    return *sh.get();
}

ADConvert::ADConvert():
    m_mcu_worker(NULL),
    m_encoder_worker(NULL)
{
    m_observer = NULL;
}

bool ADConvert::startAll(std::string pathToMCU,std::string pathToEncoder,unsigned char encoderAddr)
{

    if(false == startAcquireMcuAD(pathToMCU)) return false;

    return startAcquireAngleEncoder(pathToEncoder,encoderAddr);
}
bool ADConvert::startAcquireMcuAD(std::string pathToMCU)
{
    if(!m_mcu_worker)
        m_mcu_worker = new CMcuAcquireWorker(this,pathToMCU);
    return m_mcu_worker->start(57600);
}
bool ADConvert::startAcquireAngleEncoder(std::string pathToEncoder,unsigned char encoderAddr)
{
    if(!m_encoder_worker)
        m_encoder_worker = new CEncoderAcquireWorker(this,pathToEncoder,encoderAddr);
    return m_encoder_worker->start(115200);
}

bool ADConvert::stop()
{
    if(m_mcu_worker) m_mcu_worker->stop();
    if(m_encoder_worker) m_encoder_worker->stop();

    if(m_mcu_worker) delete m_mcu_worker;
    if(m_encoder_worker) delete m_encoder_worker;
    m_mcu_worker = NULL;
    m_encoder_worker = NULL;

    return true;
}
bool ADConvert::pause(bool yes)
{

}
void ADConvert::notify(int type)
{
    if(m_observer)
    {
        m_observer->onNotify (type,&g_AdParam);
    }
}
TQuantizationParam* ADConvert::getQuantizationValue()
{
    return &g_QuanParam;
}
TAdParam* ADConvert::getAdParam(void)
{
    return &g_AdParam;
}
void ADConvert::registerObserver(ADConvertNotify *observer)
{
    m_observer = observer;
}
