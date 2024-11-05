#include "ClientSocket.h"

ClientSocket::ClientSocket(std::string _ip) : Socket(_ip) {};

void ClientSocket::Create()
{
    socket = ::socket(hostAddrInfo->ai_family, hostAddrInfo->ai_socktype,
                      hostAddrInfo->ai_protocol);
    if (socket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        freeaddrinfo(hostAddrInfo);
        throw "ClientSocket::ClientSocket() : socket";
    }
};

ClientSocket::~ClientSocket() {
    
}

void ClientSocket::Connect()
{
    int iResult = ::connect(socket, hostAddrInfo->ai_addr, (int)hostAddrInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(socket);
        errorCode = INVALID_SOCKET;
        freeaddrinfo(hostAddrInfo);
        throw "ClientSocket::Connect : connect";
    }
    freeaddrinfo(hostAddrInfo);
}

void ClientSocket::SendMessage(std::string message)
{
    const char *cMessage = message.c_str();
    int iSendResult = send(socket, cMessage, strlen(cMessage), 0);
    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        closesocket(socket);
        throw "ClientSocket::SendMessage : send";
    }
}

std::string ClientSocket::RecvMessage(unsigned int maxSize)
{
    char *buf = new char[maxSize];
    std::string recvMessage = "";
    int iSendResult = recv(socket, buf, maxSize, 0);

    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        closesocket(socket);
        delete buf;
        throw "ClientSocket::RecvMessage : recv";
    }

    recvMessage = buf;
    delete buf;
    return recvMessage;
}