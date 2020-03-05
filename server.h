#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <map>
#include "Client.h"
#include "functions.h"

void client_loop(Client *cli, char *buf, int bufSize, int *maxfds, timeval *tv);

#endif