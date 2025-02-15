// src/server.c
#include "../include/server.h"
#include "../include/http_handler.h"
#include <stdio.h>

int initialize_server(WebServer* server, int port) {
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        return 0;
    }

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server->socket, (struct sockaddr*)&server_addr, 
            sizeof(server_addr)) == SOCKET_ERROR) {
        closesocket(server->socket);
        WSACleanup();
        return 0;
    }

    server->port = port;
    return 1;
}

void start_server(WebServer* server) {
    if (listen(server->socket, MAX_CONNECTIONS) == SOCKET_ERROR) {
        return;
    }

    printf("Server running on port %d...\n", server->port);

    while (1) {
        SOCKET client_socket = accept(server->socket, NULL, NULL);
        if (client_socket != INVALID_SOCKET) {
            handle_client_request(client_socket);
            closesocket(client_socket);
        }
    }
}

void cleanup_server(WebServer* server) {
    closesocket(server->socket);
    WSACleanup();
}