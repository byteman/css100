#include <iostream>
#include <czmq.h>
#include <Poco/Thread.h>
#include <Poco/NumberParser.h>
#include <Poco/ThreadPool.h>
using namespace std;

void*      pub_socket = NULL;
void*      sub_socket = NULL;
int send_counter = 0;
int recv_counter = 0;
void init_pub_socket(zctx_t* zctx);
void init_sub_socket(zctx_t* zcxt);
void send_msg(void);
void recv_msg(void);
void send_packet_loop();
void recv_packet_loop();
int nTimeOut = 1000;

class TPublicClass:public Poco::Runnable
{
public:
    TPublicClass(zctx_t* ctx)
        :zcxt(ctx)
    {
        init_pub_socket(zcxt);
    }
    void run()
    {

        while(1)
        {
            send_packet_loop ();
        }

    }
private:
    zctx_t* zcxt;
};
class TSubClass:public Poco::Runnable
{
 public:
    TSubClass(zctx_t* cxt):
        zcxt(cxt)
    {
        init_sub_socket(zcxt);
    }
    void run()
    {

        while(1)
        {
            recv_packet_loop ();
        }

    }
private:
    zctx_t* zcxt;
};
void send_packet_loop()
{
    while(1)
    {
        send_msg();
        Poco::Thread::sleep (nTimeOut);
    }
}
void recv_packet_loop()
{
    //init_sub_socket();
    while(1)
        recv_msg();
}
void init_pub_socket(zctx_t* zctx)
{
    int rc = 0;
    fprintf(stderr,"init_pub_socket\n");
    //zctx_t* zctx = zctx_new ();

    assert(zctx != NULL);

    pub_socket = zsocket_new (zctx,ZMQ_PUB);
    assert(pub_socket);
    //zsocket_bind (pub_socket, "tcp://%s:%d","*",5555);
    //zsocket_bind (pub_socket, "ipc:///tmp/0");
    rc = zsocket_bind (pub_socket, "inproc://thread0");
    assert(rc == 0);

    send_counter = 0;

}
struct TMsg{
    TMsg()
    {
        angle = 0;
        dist  = 0;
        speed = 0;
        counter = 0;
    }
    TMsg(double a,double d, double s)
    {
        angle = a;
        dist  = d;
        speed = s;
        counter = 0;
    }
    double angle;
    double dist;
    double speed;
    int    counter;
};
void send_msg(void)
{
    fprintf(stderr,"send_msg\n");
    TMsg msg;
    int rc = 0;
    msg.angle = 1;
    msg.dist  = 2;
    msg.speed = 3;
    msg.counter = send_counter++;
    zframe_t* zft = zframe_new (&msg,sizeof(TMsg));
    assert(zft);
    rc = zframe_send (&zft,pub_socket,0);
    assert(rc==0);
}
void recv_msg(void)
{
    fprintf(stderr,"recv_msg\n");
    TMsg *msg;
    //int rc = 0;

    zframe_t * zft = zframe_recv (sub_socket);
    assert(zft);
    if(zft)
    {
        msg = (TMsg*)zframe_data (zft);
        if(msg && (sizeof(TMsg) == zframe_size(zft)) )
        {
            recv_counter++,
            fprintf (stderr,"recv[%d]-send[%d]=%d : angle=%0.3f, dist = %0.3f ,speed= %0.3f",
                    recv_counter,
                    msg->counter,
                    msg->counter-recv_counter,
                    msg->angle,
                    msg->dist,
                    msg->speed);
        }
        zframe_destroy(&zft);
    }
}
void init_sub_socket(zctx_t* zctx)
{
    int rc = 0;
    fprintf(stderr,"init_sub_socket\n");
    //zctx_t* zctx = zctx_new ();
    assert(zctx != NULL);
    sub_socket = zsocket_new (zctx,ZMQ_SUB);
    assert(sub_socket);
    zsocket_set_subscribe (sub_socket, "");

    //rc = zsocket_connect (sub_socket, "tcp://%s:%d","localhost",5555);
    //rc = zsocket_connect (sub_socket, "ipc:///tmp/0");
    rc = zsocket_connect (sub_socket, "inproc://thread0");
    assert (rc == 0);

    recv_counter = 0;
}


void inproc_test(zctx_t* ctx)
{
    TPublicClass pub(ctx);
    TSubClass    sub(ctx);


    Poco::ThreadPool::defaultPool ().start (pub);
    Poco::ThreadPool::defaultPool ().start (sub);

    Poco::ThreadPool::defaultPool ().joinAll ();
}
int main(int argc,const char* argv[])
{
    std::string arg1 = "pub";
    std::string arg2;
    if(argc == 2)
        arg1 = argv[1];
    if(argc == 3)
    {
        arg1 = argv[1];
        arg2 = argv[2];
        Poco::NumberParser::tryParse (arg2,nTimeOut);
    }
    printf("argc = %d ,arg1=%s\n",argc,arg1.c_str ());

    zctx_t* ctx = zctx_new ();

    inproc_test(ctx);

    if(arg1 == "sub")
    {
        init_sub_socket(ctx);
        recv_packet_loop();
    }
    else if(arg1 == "pub")
    {
        init_pub_socket(ctx);
        send_packet_loop ();
    }


    cout << "Hello World!" << endl;
    return 0;
}

