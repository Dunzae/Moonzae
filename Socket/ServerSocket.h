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

    void Create();
    void Bind();
    void Listen();
    void Accept();
    void SendMessage(std::string message) override;
    std::string RecvMessage(unsigned int maxSize) override;

    //Getter and Setter
    SOCKET GetListenSocket() const;
    void SetListenSocket(SOCKET listenSocket);
    
};

#endif