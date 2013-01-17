#ifndef NETADDRESS_H
#define NETADDRESS_H
#include <iostream>
class NetAddress
{
public:
    NetAddress();
    static std::string getInterfaceAddr(const std::string &name);
};

#endif // NETADDRESS_H
