#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Socket.hpp"

Socket::Socket(char * bindIp, unsigned short bindSocket, int networkFamily, int networkType, int networkProtocal)
:
hasNoFailures(false)
{
    socketFileDesc = socket(networkFamily, networkType, networkProtocal);

    if(socketFileDesc == -1)
    {
        perror("Exception: Cannot create socket\n");
        return;
    }

    printf("Created socket: socketFileDesc=%d\n", socketFileDesc);

    sockaddr_in * bindAddress = Socket::getNewSockaddr_in(bindIp, bindSocket, networkFamily);

    //Checks if socketAddress is null
    if(!bindAddress)
    {
        perror("Exception: Failed to create new sockaddr_in\n");
        return;
    }

    /*
     *  Bind address defines address of the local machine other people can connect to.
     *  For example, machine might have two ip adress 192.168.1.1 and 192.168.1.2
     *  If you use IN_ADRANY or whatever, then people can connect on specified port of either
     *  If you bind to localhost, then only people on the local machien can connect
     */
    int bindResult = bind(socketFileDesc, (sockaddr *) bindAddress, sizeof(* bindAddress));

    if(bindResult == -1)
    {
        printf("Exception: Cannot bind address: bindIp=%s bindSocket=%hd\n", bindIp, bindSocket);
        perror(nullptr);
        return;
    }

    printf("Binded address: bindResult=%i bindIp=%s bindSocket=%hd\n", bindResult, bindIp, bindSocket);

    Socket::bindAddress = bindAddress;

    Socket::hasNoFailures = true;
}

Socket::~Socket()
{
    delete (sockaddr_in *)bindAddress;

    close(socketFileDesc);
}

bool Socket::getHasNoFailures()
{
    return hasNoFailures;
}

void Socket::setAsFailed()
{
    hasNoFailures = false;
}

int Socket::getSocketFileDescriptor()
{
    return socketFileDesc;
}

const sockaddr_in * Socket::getBindAddress()
{
    return bindAddress;
}

//Sockaddr must be deallocated
//Can return nullptr if it failed to create a valid sockaddr_in
sockaddr_in * Socket::getNewSockaddr_in(char * bindIp, unsigned short bindSocket, int networkFamily)
{
    sockaddr_in * Sockaddr = new sockaddr_in();

    if(networkFamily != AF_INET && networkFamily != AF_INET6)
    {
        printf("Exception: %i is an invalid network family\n", networkFamily);
        return NULL;
    }

    //Sets the type of connection
    Sockaddr->sin_family = networkFamily;
    //Converts socket from host to network order, Sets the socket
    Sockaddr->sin_port = htons(bindSocket);

    //Sets the ip address, Requires a null terminated string
    int conversionResult = inet_pton(AF_INET, bindIp, & Sockaddr->sin_addr);

    if(conversionResult == 0)
    {
        printf("Exception: Failed to convert %s into an integer\n", bindIp);
        return NULL;
    }

    //printf("loopy %i\n", htonl(INADDR_LOOPBACK));
    //std::cout << Sockaddr->sin_port << std::endl;
    //std::cout << Sockaddr->sin_addr.s_addr << std::endl;

    return Sockaddr;
}
