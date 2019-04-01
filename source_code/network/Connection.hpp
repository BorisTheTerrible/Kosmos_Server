#ifndef Connection_hpp
#define Connection_hpp

#include <mutex>
#include <vector>
#include <thread>

#include "Packet.hpp"

enum ConnectionStatus
{
    CONNECTING, CONNECTED, WANTS_TERMINATION, TERMINATED
};

class Connection
{
public:
    /*
        Calls the intial handshake thread.
     */
    Connection();
//public

private:
    ConnectionStatus connectionStatus;
    std::mutex connectionStatusMutex;

    /*
        Holds the packets that are yet to resolved by the main server loop.

        They need to be dealloccated when removed from the vector.
     */
    std::vector<Packet *> packets;
    std::mutex packetMutex;

    /*
        Handles the exchange of handshake packets.
        connectionStatus will be CONNECTING until
     */
    std::thread handshakeThread;

    /*
        Handles reading new data into the corresponding buffers.
        Keeps adding received data into the buffer until the full packet data is received.
        It then removes creates a Packet from that data, puts it in the Packet vector,
        and removes that data from the buffer.
     */
    std::thread socketInputThread;

    char udpBuffer[256];
    char tcpBuffer[256];

    /*
        When in CONNECTING status, used to keep track of how long the server had been waiting
        for the handshake packet from the client.

        When in CONNECTED status, used to keep track of how long ago the server last
        received a keep alive packet.
     */
    long timeout;

    void handshakeMethod();

    void socketInputMethod();
//private
};

#endif /* Connection_hpp */
