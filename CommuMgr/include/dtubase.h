#ifndef DTUBASE_H
#define DTUBASE_H
#include <vector>
#include <queue>
#include "bythread.h"
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
private:
    size_t total_tx_bytes;
    size_t total_rx_bytes;
};

#endif // DTUBASE_H
