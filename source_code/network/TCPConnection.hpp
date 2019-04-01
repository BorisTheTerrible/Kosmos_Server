#ifndef TCPConnection_hpp
#define TCPConnection_hpp

#include <arpa/inet.h>

struct sockaddr_in;

class TCPConnection
{
public:
    TCPConnection(int socketFileDesc, sockaddr_in * clientAddress);

    ~TCPConnection();

    /*
     0 is returned in the case that the socket is closed while blocking
     */
    long receiveData(void * receivedData, int receivedDataBytes);

    void sendData(void * dataToSend, int dataByteLength);

private:
    const int socketFileDesc;

    const sockaddr_in * clientAddress;
};

#endif /* TCPConnection_hpp */
