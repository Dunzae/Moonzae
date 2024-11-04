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
    std::string errorMessage; // 에러 문자열
    struct addrinfo *hostAddrInfo;
    // 호스트의 정보를 담고 있는 addrinfo 구조체

public:
    Socket(std::string _ip);
    ~Socket();

    virtual bool sendMessage(std::string message) = 0;
    virtual std::string recvMessage(unsigned int maxSize) = 0;

    bool getHostInfo();
    bool shutdown();

    // Getter
    int GetErrorCode() const;
    SOCKET GetSocket() const;
    std::string GetIp() const;
    std::string GetPort() const;
    std::string GetErrorMessage() const;
    struct addrinfo *GetHostAddrInfo() const;

    // Setter
    void SetErrorCode(int errorCode);
    void SetSocket(SOCKET socket);
    void SetIp(std::string ip);
    void SetPort(std::string port);
    void SetErrorMessage(std::string errorMessage);
    void SetHostAddrInfo(struct addrinfo* hostAddrInfo);
};

#endif