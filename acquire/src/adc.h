#ifndef ADC_H
#define ADC_H

#include <queue>
#include <iostream>
#include <vector>
#include "filter.h"
#include "acquire.h"

class CMcuAcquireWorker;
class CEncoderAcquireWorker;

struct ADConvertNotify
{
    virtual void onNotify(int type,TAdParam* ad) = 0;
};
class ADConvert
{
public:
    ADConvert();
    static ADConvert& get();
    void registerObserver(ADConvertNotify *observer);
    bool startAll(std::string pathToMCU,std::string pathToEncoder,unsigned char encoderAddr);
    bool startAcquireMcuAD(std::string pathToMCU);
    bool startAcquireAngleEncoder(std::string pathToEncoder,unsigned char encoderAddr=0);
    bool stop();
    bool pause(bool yes);
    TAdParam* getAdParam(void);
    TQuantizationParam* getQuantizationValue();
    void notify(int type);

private:
    CMcuAcquireWorker*      m_mcu_worker;
    CEncoderAcquireWorker*  m_encoder_worker;
    ADConvertNotify *m_observer;


};

#endif // ADC_H
