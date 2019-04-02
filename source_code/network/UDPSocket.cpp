#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UDPSocket.hpp"

UDPSocket::UDPSocket(char * bindIp, unsigned short bindSocket, int networkFamily)
:
Socket(bindIp, bindSocket, networkFamily, SOCK_DGRAM, IPPROTO_UDP)
{

}

long UDPSocket::receiveData(void * receivedData, int receivedDataBytes, sockaddr_in * senderAddress)
{
    if(getHasNoFailures())
    {
        socklen_t sockaddrSize = sizeof(* senderAddress);

        //The Sockaddr used in this is set to the address of the sender!
        //return how many bytes it has received
        long bytesReceived = recvfrom(getSocketFileDescriptor(), receivedData, receivedDataBytes, 0, (struct sockaddr *) senderAddress, & sockaddrSize);

        return bytesReceived;
    }
    else
    {
        //How about you actually thrown an exception????
        perror("Exception: Cannot receive from a socket that has failed to intialize properly!\n");
    }

    return -1;
}

void UDPSocket::sendData(void * dataToSend, int dataToSendBytes, char * receiverIp, short receiverSocket, int networkFamily)
{
    if(getHasNoFailures())
    {
        sockaddr_in * receiverAddress = getNewSockaddr_in(receiverIp, receiverSocket, networkFamily);

        if(!receiverAddress)
        {
            perror("Exception: Failed to create new sockaddr_in\n");
            return;
        }

        long sendResult = sendto(getSocketFileDescriptor(), dataToSend, dataToSendBytes, 0, (sockaddr *)receiverAddress ,  sizeof(* receiverAddress));

        if(sendResult == (long)-1)
        {
            printf("Exception: Cannot send to address: receiverIp=%s receiverSocket=%hd\n", receiverIp, receiverSocket);
        }

        delete receiverAddress;
    }
    else
    {
        perror("Exception: Cannot send from a socket that has failed to intialize properly!\n");
    }

}

