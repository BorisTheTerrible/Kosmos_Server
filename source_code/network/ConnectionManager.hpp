#ifndef ConnectionManager_hpp
#define ConnectionManager_hpp

#include <vector>
#include <mutex>
#include <thread>

#include "Packet.hpp"
#include "Connection.hpp"

class ConnectionManager
{
public:
    ConnectionManager();

    /*
        Needs to close connections and crap.
     */
    ~ConnectionManager();

    /*
        Called by main server logic loop.

        Moves connections that are CONNECTED from newConnections vector to the connection vector.
        Removes connections that are TERMINATED from the connection vector.
     */
    void update();

    /*
        Used to "gracefully" exit the connections when exit is called from main server.
     */
    void quit();
//public

private:
    /*
        Used to hold connections that are still CONNECTING.
        All access must be regulated by the mutex.
     */
    std::vector<Connection> newConnections;
    std::mutex newConnectionsMutex;

    /*
        Holds the connections that are connected and have completed a handshake.

        Remember: Pushing an element onto the vector will copy the object.
                  As such, it is okay to push items created on the stack into the vector.
        Remember: Objects must be intialized in constructor!
     */
    std::vector<Connection> connections;

    /*
        Used to accept new connections.
        Puts the new connections in newConnections vector.
     */
    std::thread connectionThread;

    void connectionMethod();
//private
};

#endif /* ConnectionManager_hpp */
