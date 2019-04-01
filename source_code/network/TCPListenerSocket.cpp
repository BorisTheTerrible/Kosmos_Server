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

#include "TCPListenerSocket.hpp"

TCPListenerSocket::TCPListenerSocket(char * bindIp, unsigned short bindSocket, int networkFamily, int backlog)
:
Socket(bindIp, bindSocket, networkFamily, SOCK_STREAM, IPPROTO_TCP)
{
    int result = listen(getSocketFileDescriptor(), backlog);

    if(result == -1)
    {
        perror("Exception: cannot listen!");
    }
}

TCPListenerSocket::~TCPListenerSocket()
{

}

TCPConnection * TCPListenerSocket::waitAndAccept()
{
    sockaddr_in * clientAddress = new sockaddr_in;
    socklen_t size = sizeof(* clientAddress);

    int newFileDesc = accept(getSocketFileDescriptor(), (sockaddr *) clientAddress, & size);

    return new TCPConnection(newFileDesc, clientAddress);
}

