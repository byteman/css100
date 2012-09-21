#include <Poco/Timestamp.h>
#include <Poco/Thread.h>
#include <Poco/StringTokenizer.h>
#include <Poco/NumberParser.h>
#include <Poco/String.h>
#include <glog/logging.h>
#include <yatengine.h>
#include <Poco/SingletonHolder.h>
#include "bythread.h"
#include "termcommu.h"
#include "udpdtu.h"
#define CTX_DBG
using namespace TelEngine;


static Poco::Timestamp lastDateTime,sendInfoTime;

TermCommu::TermCommu()
{
    dtu_dev = NULL;
}
bool TermCommu::start(long timeout_ms)
{
    dtu_dev = new UdpDtu();
    if(NULL==dtu_dev) return false;
    if(false == dtu_dev->start (timeout_ms)) return false;
    //ByThread::start (timeout_ms);
}
TermCommu& TermCommu::GetInstance()
{
    static Poco::SingletonHolder<TermCommu> sh;
    return *sh.get ();
}
void TermCommu::ReceiveData(void)
{

}
bool TermCommu::GetMessage(CTX_Message& msg)
{
    if(dtu_dev == NULL) return false;

    size_t data_size = dtu_dev->GetInBuffSize ();
    if(data_size > 0)
    {
        dtu_dev->RecvBuffer (data_array,data_size);
    }

    return true;
}
void TermCommu::SendMessage(std::string msgText)
{

}
bool TermCommu::CheckMessage()
{
    return false;
}
int  TermCommu::GetReceivedCount()
{
    return 0;
}
void TermCommu::ClearMessage(void)
{

}
void TermCommu::ResetCounter(void)
{

}
/*********************************************************************************************
 *从网络中捕获一个数据包，从收到的数据包中提取发送该数据包的设备ID，被呼叫的塔机ID，申请加入塔机ID
 *
***********************************************************************************************/
bool      TermCommu::DripDeviceNo(int &SenderNo, int &RightNo, int &AddNo)
{
    CTX_Message msg;
    if(GetMessage(msg))
    {
          int    right_id,addin_id,sender_id;
          double angle,position,AngleSpeed,Dang;
          DLOG(INFO) << "DripDeviceNo" << msg.context;
          //CTX_DBG("DripMainNoAndAddNo %s\n",msg.context.c_str());
          Poco::StringTokenizer token(msg.context,"N");

#ifdef CTX_DEBUG
            for(size_t i = 0 ; i < token.count(); i++)
            {
                CTX_DBG("token[%d]=%s\n",i,token[i].c_str());
            }
#endif
          if(token.count() != 7)
          {
               CTX_DBG("DripMainNoAndAddNo Error MsgCount =%d\n",token.count());
               return false;
          }

          if(!Poco::NumberParser::tryParse(Poco::trim(token[0]),sender_id))return false;
          if(!Poco::NumberParser::tryParse(Poco::trim(token[1]),right_id))return false;
          if(!Poco::NumberParser::tryParseFloat(Poco::trim(token[2]),angle))return false;
          if(!Poco::NumberParser::tryParseFloat(Poco::trim(token[3]),position))return false;
          if(!Poco::NumberParser::tryParseFloat(Poco::trim(token[4]),AngleSpeed))return false;
          if(!Poco::NumberParser::tryParseFloat(Poco::trim(token[5]),Dang))return false;
          if(!Poco::NumberParser::tryParse(Poco::trim(token[6]),addin_id))return false;

          if(sender_id > 0 && sender_id <= 20 )
          {
              SenderNo  = sender_id;
              RightNo   = right_id;
              AddNo     = addin_id;
              return true;
          }
          return false;
    }
}
/*
监听网络,申请加入网络，获取本机工作状态.

*/
void      TermCommu::WatchNetWork(int local_id,int &master_id, bool &AddState)
{
    Poco::Timestamp StartTime;
    Poco::Timestamp CurTime;
    CTX_Message msg;
    int right_id  = 0;
    int addin_id  = 0;
    int sender_id = 0;
    bool FoundM = false;


    ClearMessage(); //在申请加入之前要先把缓存的数据全部丢掉
    //listen 5s to recv rtmsg;
    ResetCounter();
    while( (CurTime-StartTime) < 10000000) //等待10s看是否能收到主机获取其他从机的数据
    {
        if(GetMessage(msg))//这个数据有可能是主机发的，也有可能是从机回应的
        {
                DLOG(INFO) << "WatchNetWork Capture Message ----> Maybe Find Master\n";
                FoundM = true;
                break;
        }

        Poco::Thread::sleep(50);

        CurTime.update();
    }

    if(FoundM)
    {
        //等待100ms，再接收一个消息,在这100ms中可能已经收到了好几个数
        Poco::Thread::sleep(100);
        if(CheckMessage())
        {
            DripDeviceNo(sender_id,right_id,addin_id);
        }
        /*
            right_id == 0: 表明这个包是从机的回应数据
            addin_id != local_id : 申请加入的塔机编号要和本机的编号一致，也就是必须是收到申请本机加入的数据包
            master_id == local_id: 主机id不能与本机id一致，因为既然收到了信号，肯定本机是从机了
        */
        while( (right_id == 0) || (addin_id != local_id) || (sender_id == local_id) ){
            Poco::Thread::sleep(10);
            if(CheckMessage())
            {
                DripDeviceNo(sender_id,right_id,addin_id);
                //DLOG(INFO）<< "DripMainNoAndAddNo Ok MainId" << sender_id << "RightId=" << right_id << "AddNo=" << addin_id;
            }
        }
        master_id = sender_id;
        CTX_DBG("WatchNetWork OK MainId=%d RightId=%d AddNo=%d\n",master_id,right_id,addin_id);
       // g_TC[m_local_id].Valide = true;
        //g_TC[m_main_id].Valide  = true;
        AddState = true;

        StartTime.update();
        CurTime=StartTime;
        CTX_DBG("[Ready Add TC] Wait Slave Ack\n");
        //再接受一个有效数据然后发送本机信息 [就是接收被查询的从机所发来的信息，必须要接收到这个消息后，才能发送，否则造成同时发送的冲突]
        //因为新加入塔机号是跟随在塔机查询信息中的，所以被查询塔机也会回应信息，而且是立即回应，而新加入塔机会等待20ms后，并且收到了该回应
        //后才会回应自己的信息,如果只有一个主机的情况下，那么主机的下一条加入指令1s内它也能收到，故可以加入成功
        while (!GetMessage(msg))
        {
            CurTime.update();
            if( (CurTime-StartTime) > 1200000)
            {
                //1200ms 等待1200ms以便接收查询塔机的回应信息
                AddState=false;
            }
            Poco::Thread::sleep(20);
            CTX_DBG("New Add TC wait [Slave RightNo Ack]\n");
        }
        if(!AddState)
        {
            CTX_DBG("[Ready Add TC] Wait Slave Ack Failed\n");
            return;
        }
        //这里为什么要回应数据,因为要发送塔机加入命令
        std::string sendInfo = "";//build_qurey_msg();
        SendMessage(sendInfo);
        lastDateTime.update();
        sendInfoTime=lastDateTime;

    }
    else
    {
        //严格要求主机在等待过程中不能收到任何一条数据,才能变为主机
        if( GetReceivedCount() > 0) //虽然没有收到正确的数据，但是有可能是收到了乱码。所以也不能让其加入网络
        {
            CTX_DBG("WatchNetwork Failed beacuse of GetReceivedCount=%d\n",GetReceivedCount());
            AddState  = false;
        }
        else
        {
            AddState  = true;
        }

    }

}
void TermCommu::service(void)
{

}
