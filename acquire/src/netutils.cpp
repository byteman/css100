#include "netutils.h"
#include <Poco/Net/Net.h>
#include <Poco/Net/NetworkInterface.h>
#include <iostream>

using Poco::Net::NetworkInterface;

NetAddress::NetAddress()
{
    Poco::Net::NetworkInterface nt;

}

std::string NetAddress::getInterfaceAddr(const std::string &name)
{
    std::string defaddr = "localhost";
    NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
    if(list.empty()) return defaddr;

    for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
    {
#if 0
        std::cout << "Name:        " << it->name() << std::endl;
        std::cout << "DisplayName: " << it->displayName() << std::endl;
        std::cout << "Address:     " << it->address().toString() << std::endl;
        std::cout << "Subnet:      " << it->subnetMask().toString() << std::endl;
        std::cout << "Broadcast:   " << it->broadcastAddress().toString() << std::endl;
        std::cout << "Index:       " << it->index() << std::endl;
#endif
        if(it->name() == name)
        {
            return it->address().toString();
        }
    }
    return defaddr;
}

