#include "Client.h"

#define BACKLOG 0    // Max number of waiting connections

Client::Client(int port) : port(port)
{
    connLen = sizeof(conn);
    msgSoc = -1;
    soc = -1;
    openSockets = fd_set();
    readSockets = fd_set();

    gpio = new GpioOpt;         // obj to control the lights
};

Client::~Client() 
{
    delete gpio;
}

void Client::ParseCommand(std::string command)
{
    if (command == std::string("on")) {
        gpio->turn_all_on();
    } else if (command == "off") {
        gpio->turn_all_off();
    }
}