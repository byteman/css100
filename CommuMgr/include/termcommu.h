#ifndef TERMCOMMU_H
#define TERMCOMMU_H
#include "dtubase.h"
struct CTX_Message{
  CTX_Message()
  {
      wType   = 0;
      context = "";
  }
  unsigned short   wType;              //消息类型
  std::string      context;
};

class TermCommu:public ByThread
{
public:
    TermCommu();
    static TermCommu& GetInstance();
    bool start(long timeout_ms=1000);
    bool DripDeviceNo(int &MainNo, int &RightNo, int &AddNo);
    void WatchNetWork(int local_id,int &master_id, bool &AddState);

    void ReceiveData(void);
    bool GetMessage(CTX_Message& msg);
    void SendMessage(std::string msgText);
    bool CheckMessage();
    int  GetReceivedCount();
    void ClearMessage(void);
    void ResetCounter(void);
    virtual void service(void);
private:
    DtuBase* dtu_dev;
    DtuBase::TDataArray data_array;
};

#endif // TERMCOMMU_H
