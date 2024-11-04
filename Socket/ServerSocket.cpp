#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H___

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "ServerSocket.h"

bool ServerSocket::createListenSocket()
{
    listenSocket = ::socket(hostAddrInfo->ai_family, hostAddrInfo->ai_socktype, hostAddrInfo->ai_protocol);
    if (listenSocket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Create Listen Socket Error";
        freeaddrinfo(hostAddrInfo);
        return false;
    }
    return true;
}

bool ServerSocket::bind()
{
    int iResult = ::bind(listenSocket, hostAddrInfo->ai_addr, (int)hostAddrInfo->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Bind Error";
        freeaddrinfo(hostAddrInfo);
        closesocket(listenSocket);
        return false;
    }
    freeaddrinfo(hostAddrInfo);
    return true;
}

bool ServerSocket::listen()
{
    int iResult = ::listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Listen Error";
        closesocket(listenSocket);
        return false;
    }
    return true;
}

bool ServerSocket::accept()
{
    socket = ::accept(listenSocket, NULL, NULL);
    if (socket == INVALID_SOCKET)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Accept Error";
        closesocket(listenSocket);
        return false;
    }
    return true;
}

bool ServerSocket::sendMessage(std::string message)
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

std::string ServerSocket::recvMessage(unsigned int maxSize)
{
    char* buf = new char[maxSize];
    std::string recvMessage = "";
    int iSendResult = recv(socket, buf, maxSize, 0);
    
    if (iSendResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Send Error";
        closesocket(socket);
        delete buf;
        return "";
    }

    recvMessage = buf;
    delete buf;
    return recvMessage;
}

bool ServerSocket::shutdownClient()
{
    int iResult = ::shutdown(socket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        errorCode = WSAGetLastError();
        errorMessage = "Shutdown Error";
        closesocket(socket);
        return false;
    }
    return true;
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