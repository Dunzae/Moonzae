#undef UNICODE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include "ServerSocket.h"

#pragma comment(lib, "Ws2_32.lib")

int __cdecl main(void)
{
    int error = 0;
    ServerSocket server{"127.0.0.1"};

    try {
        server.GetHostInfo();
        server.Create();
        server.Bind();
        server.Listen();
        server.Accept();
        server.SendMessage("안녕하세요");
        server.Shutdown();

    } catch(std::string errorMessage) {
        std::cout << "ErrorMessage : " << errorMessage << std::endl;
        return 1;
    }
    return 0;
}