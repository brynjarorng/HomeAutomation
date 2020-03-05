#include "server.h"

using namespace std;

void client_loop(Client *cli, char *buf, int bufSize, int *maxfds, timeval *tv)
{
    cli->readSockets = fd_set(cli->openSockets);
    memset(buf, 0, bufSize);
    int n = select(*maxfds + 1, &cli->readSockets, NULL, NULL, tv);
    
    if(n < 0)
    {
        perror("select failed ");
        exit(-1);
    }
    else
    {
        if(FD_ISSET(cli->soc, &cli->readSockets))
        {
            if((cli->msgSoc = accept(cli->soc, (struct sockaddr *)&cli->conn, &cli->connLen)) > 0)
            {
                cout << "Client connected! " << endl;
            }
            else
            {
                cout << "Failed to connect! " << endl;
            }
        }

        
        FD_SET(cli->msgSoc, &cli->openSockets);
        *maxfds = max(*maxfds, cli->msgSoc);

        while(n-- > 0)
        {
            // Check if message is waiting and read
            if(FD_ISSET(cli->msgSoc, &cli->readSockets))
            {
                if(read(cli->msgSoc, buf, bufSize) == 0)
                {
                    // close connection to client
                    cout << "Client disconnected" << endl;
                    close(cli->msgSoc);
                    FD_CLR(cli->msgSoc, &cli->openSockets);
                    cli->msgSoc = -1; 
                }
                else
                {
                    cout << "COMMAND: " << buf << endl;
                    cli->ParseCommand(std::string(buf));
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: <application name> <port>\n");
        exit(0);
    }

    int clientPort = atoi(argv[1]);

    struct timeval tv;                  // Struct to configure the select() waiting time
    int bufCliSize = 5002;              // Buffer size for client
    Client cli(clientPort);             // Socket to listen for a client
    char bufCli[bufCliSize];            // Buffer to read from
    int maxfdsCli = 0;                  // Max filedescriptors

    // Set wait time for messages
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    
    // Setup client listening
    // Get client socket
    cli.soc = open_soc(clientPort);

    // bind to address
    bind_socket(&cli.conn, cli.soc, cli.port);

    // listen for client
    listen_socket(&maxfdsCli, cli.soc, &cli.openSockets);

    printf("Listening on socket: %s\n", argv[1]);

    // ignore the interupt when trying to send to a server that may DC mid transmition
    //signal(SIGPIPE, SIG_IGN);

    // Main loop
    while(true)
    {
        client_loop(&cli, bufCli, bufCliSize, &maxfdsCli, &tv);

        usleep(5000);
    }
    
}