#ifndef DTUBASE_H
#define DTUBASE_H
#include <vector>
#include <queue>
#include "bythread.h"
struct INotify
{
    void OnDataRecived(unsigned char *buffer,size_t len);
};
class DtuBase:public ByThread
{
public:
    typedef std::vector<unsigned char> TDataArray;
    typedef std::queue<unsigned char>  TDataQueue;
    DtuBase();
    virtual ~DtuBase();
    virtual int     SendBuffer(unsigned char *buffer,size_t len);
    virtual bool    RecvBuffer(TDataArray& dataBuf, size_t len);
    virtual size_t  GetInBuffSize(void);
    virtual void    FlushInBuffer(void);
    virtual void    FlushOutBuffer(void);
    size_t  GetTotalSendBytes(void);
    size_t  GetTotalRecvBytes(void);
    void    RegisterObserver(INotify* obj);
    void    Notify(unsigned char *buffer,size_t len);
private:
    size_t total_tx_bytes;
    size_t total_rx_bytes;
    INotify* m_obj;
};

#endif // DTUBASE_H
