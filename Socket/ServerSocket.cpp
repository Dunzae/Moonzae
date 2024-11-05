#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H___

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "ServerSocket.h"

void ServerSocket::Create()
{
    listenSocket = ::socket(hostAddrInfo->ai_family, hostAddrInfo->ai_socktype, hostAddrInfo->ai_protocol);
    if (listenSocket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        freeaddrinfo(hostAddrInfo);
        throw "ServerSocket::Create";
    }
}

void ServerSocket::Bind()
{
    int iResult = ::bind(listenSocket, hostAddrInfo->ai_addr, (int)hostAddrInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        freeaddrinfo(hostAddrInfo);
        closesocket(listenSocket);
        throw "ServerSocket::Bind";
    }
    freeaddrinfo(hostAddrInfo);
}

void ServerSocket::Listen()
{
    int iResult = ::listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        closesocket(listenSocket);
        throw "ServerSocket::Listen";
    }
}

void ServerSocket::Accept()
{
    socket = ::accept(listenSocket, NULL, NULL);
    if (socket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        closesocket(listenSocket);
        throw "ServerSocket::Accept";
    }
}

void ServerSocket::SendMessage(std::string message)
{
    const char *cMessage = message.c_str();
    int iSendResult = send(socket, cMessage, strlen(cMessage), 0);
    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        closesocket(socket);
        throw "ServerSocket::SendMessage";
    }
}

std::string ServerSocket::RecvMessage(unsigned int maxSize)
{
    char *buf = new char[maxSize];
    std::string recvMessage = "";
    int iSendResult = recv(socket, buf, maxSize, 0);

    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        closesocket(socket);
        delete buf;
        throw "ServerSocket::RecvMessage";
    }

    recvMessage = buf;
    delete buf;
    return recvMessage;
}

SOCKET ServerSocket::GetListenSocket() const
{
    return listenSocket;
}

void ServerSocket::SetListenSocket(SOCKET listenSocket)
{
    listenSocket = listenSocket;
}

#endif