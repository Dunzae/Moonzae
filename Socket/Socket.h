#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>

class Socket
{
protected:
    int errorCode;           // 에러 코드
    SOCKET socket;           // 상대방과 연결된 소켓
    std::string ip;          // 상대방의 ip
    std::string port;        // 상대방의 port
    struct addrinfo *hostAddrInfo;
    // 호스트의 정보를 담고 있는 addrinfo 구조체

public:
    Socket(std::string _ip);
    ~Socket();

    virtual void SendMessage(std::string message) = 0;
    virtual std::string RecvMessage(unsigned int maxSize) = 0;

    void GetHostInfo();
    void Shutdown();

    // Getter
    int GetErrorCode() const;
    SOCKET GetSocket() const;
    std::string GetIp() const;
    std::string GetPort() const;
    struct addrinfo *GetHostAddrInfo() const;

    // Setter
    void SetErrorCode(int errorCode);
    void SetSocket(SOCKET socket);
    void SetIp(std::string ip);
    void SetPort(std::string port);
    void SetHostAddrInfo(struct addrinfo* hostAddrInfo);
};

#endif