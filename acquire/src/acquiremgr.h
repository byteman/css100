#ifndef ACQUIREMGR_H
#define ACQUIREMGR_H
#include "bythread.h"
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/DatagramSocket.h>
class AcquireMgr:public ByThread
{
public:
    AcquireMgr();
    static AcquireMgr& get();

    virtual bool before_run();
    virtual void service ();
private:
    Poco::Net::DatagramSocket  acq_socket;
    unsigned char acq_buf[1024];
};

#endif // ACQUIREMGR_H
