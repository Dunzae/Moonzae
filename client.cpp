#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include "ClientSocket.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

int __cdecl main(int argc, char **argv)
{
    ClientSocket client("127.0.0.1");
    if(!client.getHostInfo()) {
        std::cout << "errorCode : " << client.GetErrorCode() << std::endl;
        std::cout << "errorMessage : " << client.GetErrorMessage() << std::endl;
        return 1;
    }

    if(!client.connect()) {
        std::cout << "errorCode : " << client.GetErrorCode() << std::endl;
        std::cout << "errorMessage : " << client.GetErrorMessage() << std::endl;
        return 1;
    }

    std::string message;
    message = client.recvMessage(256);
    if(message == "") {
        std::cout << "errorCode : " << client.GetErrorCode() << std::endl;
        std::cout << "errorMessage : " << client.GetErrorMessage() << std::endl;
        return 1;
    } else {
        std::cout << message << std::endl;
    }

    if (!client.shutdown()) {
        std::cout << "errorCode : " << client.GetErrorCode() << std::endl;
        std::cout << "errorMessage : " << client.GetErrorMessage() << std::endl;
        return 1;
    }

    return 0;
}