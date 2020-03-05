#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <string.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <string.h>
#include <iostream>
#include "GpioOpt.h"

// Class for basic connection details fot the client
class Client
{
    public:
        int soc;                    // Socket for the client
        int msgSoc;                 // Socket to get msgs
        int port;                   // port to listen to the client
        struct sockaddr_in conn;    // Connection detaild for the client
        fd_set openSockets;         // FD set to listen
        fd_set readSockets;         // Socket list for select()
        fd_set exceptSockets;       // Exception socket list
        socklen_t connLen;          // Connection length
    
    Client(int port);
    ~Client();
    void ParseCommand(std::string command);  // Parse the command from the client

    
    private:
        GpioOpt *gpio;
};

#endif