#include "dtubase.h"

DtuBase::DtuBase()
{
     total_tx_bytes = total_rx_bytes = 0;
     m_obj = NULL;
}

DtuBase::~DtuBase()
{

}
void    DtuBase::Notify(unsigned char *buffer,size_t len)
{
    if(m_obj)
    {
        m_obj->OnDataRecived (buffer,len);
    }
}
int     DtuBase::SendBuffer(unsigned char *buffer,size_t len)
{
    return 0;
}
bool    DtuBase::RecvBuffer(TDataArray& dataBuf, size_t len)
{
    return 0;
}
size_t  DtuBase::GetInBuffSize(void)
{
    return 0;
}
void    DtuBase::FlushInBuffer(void)
{

}
void    DtuBase::FlushOutBuffer(void)
{

}
size_t  DtuBase::GetTotalSendBytes(void)
{
    return total_tx_bytes;
}
size_t  DtuBase::GetTotalRecvBytes(void)
{
    return total_rx_bytes;
}
