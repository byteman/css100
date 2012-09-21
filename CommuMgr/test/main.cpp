#include <unistd.h>
#include "bythread.h"
#include "termcommu.h"
int main(int argc, char *argv[])
{
    int master = 0;
    bool add = false;
    TermCommu::GetInstance ().start (1000);
    TermCommu::GetInstance ().WatchNetWork (1,master,add);

    pause();
    return 0;
}
