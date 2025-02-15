// include/server.h
#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>

#define DEFAULT_PORT 9090
#define MAX_CONNECTIONS 10

typedef struct {
    SOCKET socket;
    int port;
} WebServer;

int initialize_server(WebServer* server, int port);
void start_server(WebServer* server);
void cleanup_server(WebServer* server);

#endif