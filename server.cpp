#undef UNICODE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include "ServerSocket.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

int __cdecl main(void)
{
    int error = 0;
    SOCKET ListenSocket;
    SOCKET ClientSocket;
    ServerSocket server{"127.0.0.1"};

    if (!server.getHostInfo())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.createListenSocket())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.bind())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.listen())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.accept())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.sendMessage((std::string) "안녕하세요"))
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    if (!server.shutdown())
    {
        std::cout << "ErrorCode : " << server.GetErrorCode() << std::endl;
        std::cout << "ErrorMessage : " << server.GetErrorMessage() << std::endl;
        return 1;
    }

    return 0;
}