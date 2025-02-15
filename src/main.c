// src/main.c
#include "../include/server.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    WebServer server;
    int port = argc > 1 ? atoi(argv[1]) : DEFAULT_PORT;

    if (!initialize_server(&server, port)) {
        printf("Failed to initialize server\n");
        return 1;
    }

    start_server(&server);
    cleanup_server(&server);
    return 0;
}