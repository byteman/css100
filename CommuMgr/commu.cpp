#include <yatengine.h>
#include "commu.h"
using namespace TelEngine;
namespace { // anonymous

class Commu : public Plugin
{
public:
    Commu();
    ~Commu();
    virtual void initialize();
    virtual bool isBusy() const;
private:
    bool m_first;
};

static Mutex s_mutex(true,"RManager");

Commu::Commu()
    : Plugin("commu"),
      m_first(true)
{
    Output("Haha^^^^,Loaded module Commu");
}
bool Commu::isBusy() const
{
    return false;
}
Commu::~Commu()
{
    Output("Unloading module RManager");
    Debugger::setIntOut(0);
}
void Commu::initialize()
{
    if (m_first) {
        Output("Initializing module Commu");
        Configuration cfg;
        cfg = Engine::configFile("commu");

    }
}

INIT_PLUGIN(Commu);

}
