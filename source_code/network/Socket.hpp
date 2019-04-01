#ifndef Socket_hpp
#define Socket_hpp

struct sockaddr_in;

class Socket
{
    protected:
        Socket(char * bindIp, unsigned short bindSocket, int networkFamily, int networkType, int networkProtocal);
        ~Socket();
        sockaddr_in * getNewSockaddr_in(char * bindIp, unsigned short bindSocket, int networkFamily);
        bool getHasNoFailures();
        void setAsFailed();
        int getSocketFileDescriptor();
        int getNetworkFamily();
        const sockaddr_in * getBindAddress();

    private:
        int socketFileDesc;
        sockaddr_in * bindAddress;
        bool hasNoFailures;
};

#endif /* Socket_hpp */
