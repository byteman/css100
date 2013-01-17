#ifndef VIRTUALADC_H
#define VIRTUALADC_H
#include <queue>
#include <iostream>
#include <vector>
#include "filter.h"
#include "acquire.h"
#include "adc.h"
#include <Poco/Thread.h>
class VirtualAdc:public ADConvert,public Poco::Runnable
{
public:
    VirtualAdc();
    static VirtualAdc& get();
    void registerObserver(ADConvertNotify *observer);
    bool startAll(std::string pathToMCU,std::string pathToEncoder,unsigned char encoderAddr);
    bool startAcquireMcuAD(std::string pathToMCU);
    bool startAcquireAngleEncoder(std::string pathToEncoder,unsigned char encoderAddr=0);
    bool stop();
    bool pause(bool yes);
    TAdParam* getAdParam(void);
    TQuantizationParam* getQuantizationValue();
    void notify(int type);
    virtual void run();

private:
    void calc_rt_value(unsigned char data[],size_t len);
    ADConvertNotify *m_observer;


};

#endif // VIRTUALADC_H
