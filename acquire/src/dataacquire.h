#ifndef DATAACQUIRE_H
#define DATAACQUIRE_H

#include <queue>
#include <iostream>
#include <vector>
#include "filter.h"
#include "acquire.h"
#include "dataacquire.h"
#include "adc.h"
#include "virtualadc.h"
#include "normalizer.h"
#include "acquire.h"
class CDataAcquire:public ADConvertNotify
{
public:
    CDataAcquire();
    static CDataAcquire& get();

    bool start();
    bool stop();
    bool pause(bool yes);
    void onNotify(int type,TAdParam* ad);
    TQuantizationParam* getQuantizaterValue();
    TRunParam* getNormalizerValue();
    void addObserver(CollectorNotify*     observer);
    void removeObserver(CollectorNotify*  observer);
    int  calibrateZero(EnumCalibType type, double value);
    int  calibrateValue(EnumCalibType type,double value);
    bool calibrateSave(EnumCalibType type);
    ADConvert   m_adc;
    //VirtualAdc  m_adc;
    Normalizer  m_normalizer;

private:
    int getCurAD(EnumCalibType type);
    CollectorNotify*     m_observer;

};

#endif // DATAACQUIRE_H
