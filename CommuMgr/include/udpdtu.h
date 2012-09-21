#ifndef UDPDTU_H
#define UDPDTU_H

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include "dtubase.h"

class UdpDtu:public DtuBase
{
public:
    UdpDtu();
    virtual ~UdpDtu();
    virtual int     SendBuffer(unsigned char *buffer,size_t len);
    virtual bool    RecvBuffer(TDataArray& dataBuf, size_t len);
    virtual size_t  GetInBuffSize(void);
    virtual void    FlushInBuffer(void);
    virtual void    FlushOutBuffer(void);
    virtual void    service();
private:
    Poco::Net::DatagramSocket  udp_socket;
    Poco::Net::SocketAddress   remote_address;
    unsigned char   recv_buffer[1024];
    TDataQueue      data_queue;
};

#endif // UDPDTU_H
