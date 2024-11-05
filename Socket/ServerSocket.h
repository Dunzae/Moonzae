#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H___

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "Socket.h"

class ServerSocket : public Socket
{
private:
    SOCKET listenSocket;
    

public:
    ServerSocket(std::string _ip) : Socket{_ip}{};
    ~ServerSocket() {};

    bool createListenSocket();
    bool bind();
    bool listen();
    bool accept();
    bool sendMessage(std::string message) override;
    std::string recvMessage(unsigned int maxSize) override;
    bool shutdownClient();

    //Getter and Setter
    SOCKET GetListenSocket() const;
    void SetListenSocket(SOCKET listenSocket);
    
};

#endif