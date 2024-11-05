#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H___

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "Socket.h"

class ClientSocket : public Socket
{
public:
    ClientSocket(std::string _ip) : Socket{_ip} {};
    ~ClientSocket() {};

    bool connect();
    bool sendMessage(std::string message) override;
    std::string recvMessage(unsigned int maxSize) override;
};

#endif