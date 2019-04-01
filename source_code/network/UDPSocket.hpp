#ifndef UDPSocket_hpp
#define UDPSocket_hpp

#include "Socket.hpp"

class UDPSocket : public Socket
{
    public:
        UDPSocket(char * bindIp, unsigned short bindSocket, int networkFamily);
        long receiveData(void * receivedData, int receivedDataBytes, sockaddr_in * senderAddress);
        void sendData(void * dataToSend, int sentDataBytes, char * receiverIp, short receiverSocket, int networkFamily);
};

#endif /* UDPSocket_hpp */
