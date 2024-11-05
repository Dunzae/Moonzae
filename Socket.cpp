#include "Socket.h"

Socket::Socket(std::string _ip) : errorCode{0}, socket{INVALID_SOCKET}, ip{_ip},
                                  port{"27015"}, errorMessage{""}, hostAddrInfo{nullptr}
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        errorCode = iResult;
        errorMessage = "WSAStartup Error";
        return;
    }
}

Socket::~Socket()
{
    if (socket != INVALID_SOCKET)
        closesocket(socket);
    WSACleanup();
}

bool Socket::getHostInfo()
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
        errorMessage = "GetAddrInfo Error";
        return false;
    }
    return true;
}

bool Socket::shutdown()
{
    int iResult = ::shutdown(socket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Shutdown error";

        closesocket(socket);
        socket = INVALID_SOCKET;

        return false;
    }
    return true;
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

std::string Socket::GetErrorMessage() const
{
    return errorMessage;
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

void Socket::SetErrorMessage(std::string errorMessage)
{
    errorMessage = errorMessage;
}

void Socket::SetHostAddrInfo(struct addrinfo* hostAddrInfo)
{
    hostAddrInfo = hostAddrInfo;
}