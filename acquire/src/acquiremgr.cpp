#include "acquiremgr.h"
#include "netutils.h"
#include <cstdio>
#include <Poco/SingletonHolder.h>
#include "acquire.h"
#include <string.h>

typedef struct _AcquireCmd{
    int cmd;
    int int_arg1;
    int int_arg2;
    double dbl_arg1;
    double dbl_arg2;
}AcquireCmd;
AcquireMgr::AcquireMgr()
{
}
AcquireMgr& AcquireMgr::get()
{
    static Poco::SingletonHolder<AcquireMgr> sh;
    return *sh.get ();
}
bool AcquireMgr::before_run()
{
     printf ("AcquireMgr before_run\n");
    Poco::Net::SocketAddress addr(NetAddress::getInterfaceAddr ("eth0"),5556);
    acq_socket.bind (addr,true);
    return true;
}
void AcquireMgr::service ()
{
    printf ("AcquireMgr service\n");
    int len = acq_socket.receiveBytes (acq_buf,1024);
    printf("AcquireMgr recv=%d\n",len);

    if(len == sizeof(AcquireCmd))
    {
        AcquireCmd cmd;
        cmd.int_arg2 = 1;
        memcpy(&cmd,acq_buf,len);
        if(cmd.cmd == 1) //calibrate zero
        {
            bool ret = Collector::get ().calibrateZero ((EnumCalibType)cmd.int_arg1,cmd.dbl_arg1);
            cmd.int_arg2 = ret?0:1;
        }else if(cmd.cmd == 2) //calibrate value
        {
            bool ret = Collector::get ().calibrateValue ((EnumCalibType)cmd.int_arg1,cmd.dbl_arg1);
            cmd.int_arg2 = ret?0:1;
        }else if(cmd.cmd == 3) //calibrate save
        {
            bool ret = Collector::get ().calibrateSave ((EnumCalibType)cmd.int_arg1);
            cmd.int_arg2 = ret?0:1;
        }
        acq_socket.sendBytes (&cmd,len);
    }

}
