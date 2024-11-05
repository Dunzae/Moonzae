#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include "ClientSocket.h"

#pragma comment(lib, "Ws2_32.lib")

int __cdecl main(int argc, char **argv)
{
    ClientSocket client("127.0.0.1");
    try {
        client.GetHostInfo();
        client.Create();
        client.Connect();

        std::string message;
        message = client.RecvMessage(256);
        std::cout << message << std::endl;

        client.Shutdown();
    } catch(std::string errorMessage) {
        std::cout << "ErrorMessage : " << errorMessage << std::endl;
        return 1;
    }
    return 0;
}