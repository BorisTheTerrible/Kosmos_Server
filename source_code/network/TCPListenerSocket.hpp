#ifndef TCPListenerSocket_hpp
#define TCPListenerSocket_hpp

#include <stdio.h>

#include "Socket.hpp"

class TCPConnection;

class TCPListenerSocket : public Socket
{
public:
    TCPListenerSocket(char * bindIp, unsigned short bindSocket, int networkFamily, int backlog);
    TCPConnection * waitAndAccept();
    ~TCPListenerSocket();
};

#endif /* TCPListenerSocket_hpp */
