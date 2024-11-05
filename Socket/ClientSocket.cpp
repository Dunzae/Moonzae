#include "ClientSocket.h"

bool ClientSocket::connect()
{
    socket = ::socket(hostAddrInfo->ai_family, hostAddrInfo->ai_socktype,
                      hostAddrInfo->ai_protocol);
    if (socket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Socket Create Error";
        freeaddrinfo(hostAddrInfo);
        return false;
    }

    int iResult = ::connect(socket, hostAddrInfo->ai_addr, (int)hostAddrInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(socket);
        errorCode = INVALID_SOCKET;
        errorMessage = "Connect Error";
        freeaddrinfo(hostAddrInfo);
        return false;
    }

    freeaddrinfo(hostAddrInfo);
    return true;
}

bool ClientSocket::sendMessage(std::string message)
{
    const char *cMessage = message.c_str();
    int iSendResult = send(socket, cMessage, strlen(cMessage), 0);
    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Send Error";
        closesocket(socket);
        return false;
    }
    return true;
}

std::string ClientSocket::recvMessage(unsigned int maxSize)
{
    char *buf = new char[maxSize];
    std::string recvMessage = "";
    int iSendResult = recv(socket, buf, maxSize, 0);

    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Recv Error";
        closesocket(socket);
        delete buf;
        return "";
    }

    recvMessage = buf;
    delete buf;
    return recvMessage;
}