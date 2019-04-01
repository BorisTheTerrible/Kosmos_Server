#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TCPConnection.hpp"

TCPConnection::TCPConnection(int socketFileDesc, sockaddr_in * clientAddress)
:
socketFileDesc(socketFileDesc), clientAddress(clientAddress)
{

}

TCPConnection::~TCPConnection()
{
    close(socketFileDesc);
}

long TCPConnection::receiveData(void * receivedData, int receivedDataBytes)
{
    //Last value is integer used for flags
    long dataByteLength = recv(socketFileDesc, receivedData, receivedDataBytes, 0);

    std::cout << strerror(errno) << std::endl;

    return dataByteLength;
}

void TCPConnection::sendData(void * dataToSend, int dataByteLength)
{
    //Last value is integer used for flags
    send(socketFileDesc, dataToSend, dataByteLength, 0);
}
