#ifndef TERMCOMMU_H
#define TERMCOMMU_H
#include "dtubase.h"


#define     MAX_LEN         8192
/*
�����ն���Ϣ
*/
struct CTX_Message{
  CTX_Message()
  {
      wType   = 0;
      context = "";
  }
  unsigned short   wType;              //��Ϣ����
  std::string      context;
};

/*
�����豸֮�为��ͨѶ��ģ��
*/
class TermCommu:public INotify
{
public:
    TermCommu();
    static TermCommu& GetInstance();
    bool start(long timeout_ms=1000);


    /*
    ��ȡ�ź�ǿ��
    */
    int  GetSignal(void);
    void ParseData(void);
    void OnDataRecived(unsigned char *buffer,size_t len);
    void ReceiveDataThread(void);
    bool DripDeviceNo(int &MainNo, int &RightNo, int &AddNo);
    void WatchNetWork(int local_id,int &master_id, bool &AddState);
    int  GetMessage(CTX_Message& msg,int type=1, int timeout_ms=1000);
    size_t  CheckMessage(int type=1);
    int  SendMessage(CTX_Message& msg);
    int  SendMessage(std::string& msg);

    int  GetReceivedCount();
    void ClearMessage(void);
    void ResetCounter(void);
private:

    void ParseRecvData(char c);


    DtuBase* dtu_dev;
    DtuBase::TDataArray data_array;
    DtuBase::TDataQueue data_queue;
    std::queue<CTX_Message> m_msg_que;
    std::queue<CTX_Message> m_ws_msg_que;
    std::queue<CTX_Message> m_height_msg_que;
    unsigned char m_receive_byte_count;

    bool    m_allow_send;
    int     m_receive_msg_count;
    int     m_signal;
    Poco::Timestamp             m_upload_stamp;
    char  m_tmp[MAX_LEN];
    int   m_pos;
    bool  m_start_flag;
};

#endif // TERMCOMMU_H
