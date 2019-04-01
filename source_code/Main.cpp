#include <stdio.h>
#include <string.h>
#include <iostream>
#include <bitset>
#include <codecvt>
#include <locale.h>
#include <exception>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Environment.hpp"
#include "network/UDPSocket.hpp"
#include "network/TCPListenerSocket.hpp"
#include "network/TCPConnection.hpp"
#include "utilities/Logger.hpp"

struct HandshakePacket
{
    unsigned short id = 1;
    unsigned short dataSize = 32;

    /* Data */
    unsigned short clientVersion;
    char PAD[2];
    char16_t username[32];
    char16_t password[32];
};


void serverStart()
{
    TCPListenerSocket tcpListenerSocket("127.0.0.1", 30000u, AF_INET, 10);
    TCPConnection * tpcConnection = tcpListenerSocket.waitAndAccept();
    std::cout << "Connected!";

    HandshakePacket handshakePacket;
    handshakePacket.clientVersion = 0;

    delete tpcConnection;
}

int main(int argumentCount, const char * arguments[])
{
    using namespace std;

    char value;
    cin >> value;

    if(value == 'c')
    {

    }
    else if(value == 's')
    {
        LOG("HELLER", LoggerLevels::Summary);
        loggerConsoleLoggingLevel = LoggerLevels::Warning;
        LOG("Poop", LoggerLevels::Summary);
        LOG("Turd", LoggerLevels::Severe);
        serverStart();
    }

    return 0;
}

