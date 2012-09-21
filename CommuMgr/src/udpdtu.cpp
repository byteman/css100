#include "udpdtu.h"

using namespace Poco::Net;

#define REMOTE_IP   "192.168.50.255"
#define REMOTE_PORT 9999
UdpDtu::UdpDtu()
{
    remote_address = SocketAddress(REMOTE_IP,REMOTE_PORT);

}
UdpDtu::~UdpDtu()
{

}
int     UdpDtu::SendBuffer(unsigned char *buffer,size_t len)
{
    udp_socket.sendTo (buffer,len,remote_address);
    return 0;
}
bool    UdpDtu::RecvBuffer(TDataArray& dataBuf, size_t len)
{
    dataBuf.clear ();
    if(len > data_queue.size ()) len = data_queue.size ();

    for(int i = 0 ; i < len; i++)
    {
        dataBuf.push_back (data_queue.front ());
        data_queue.pop ();
    }

    return 0;
}
size_t  UdpDtu::GetInBuffSize(void)
{
    return data_queue.size();
}
void    UdpDtu::FlushInBuffer(void)
{

}
void    UdpDtu::FlushOutBuffer(void)
{

}
void    UdpDtu::service()
{
    Poco::Timespan span(250000);

    if (udp_socket.poll(span, Poco::Net::Socket::SELECT_READ))
    {
            try
            {
                    SocketAddress sender;
                    int n = udp_socket.receiveFrom((unsigned char*)&recv_buffer, sizeof(recv_buffer), sender);
                    for(int i = 0; i < n; i++)
                    {
                        data_queue.push (recv_buffer[i]);
                    }
            }
            catch (Poco::Exception& exc)
            {

            }
    }
}
