#include "Socket.h"

Socket::Socket(std::string _ip) : errorCode{0}, socket{INVALID_SOCKET}, ip{_ip},
                                  port{"27015"}, hostAddrInfo{nullptr}
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        errorCode = iResult;
        throw "Socket::Socket WSAStartup";
    }
}

Socket::~Socket()
{
    if (socket != INVALID_SOCKET)
        closesocket(socket);
    WSACleanup();
}

void Socket::GetHostInfo()
{
    struct addrinfo hints{0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &hostAddrInfo);
    if (iResult != 0)
    {
        errorCode = iResult;
        throw "Socket::GetAddrInfo";
    }
}

void Socket::Shutdown()
{
    int iResult = ::shutdown(socket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();

        closesocket(socket);
        socket = INVALID_SOCKET;

        throw "Socket::Shutdown";
    }
}

int Socket::GetErrorCode() const
{
    return errorCode;
}

SOCKET Socket::GetSocket() const
{
    return socket;
}

std::string Socket::GetIp() const
{
    return ip;
}

std::string Socket::GetPort() const
{
    return port;
}

struct addrinfo* Socket::GetHostAddrInfo() const
{
    return hostAddrInfo;
}

void Socket::SetErrorCode(int errorCode)
{
    errorCode = errorCode;
}

void Socket::SetSocket(SOCKET socket)
{
    socket = socket;
}

void Socket::SetIp(std::string ip)
{
    ip = ip;
}

void Socket::SetPort(std::string port)
{
    port = port;
}

void Socket::SetHostAddrInfo(struct addrinfo* hostAddrInfo)
{
    hostAddrInfo = hostAddrInfo;
}