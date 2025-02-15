// src/http_handler.c
#include "../include/http_handler.h"
#include "../include/mime_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void send_http_response(SOCKET client_socket, const char* status,
                             const char* content_type, const char* content,
                             size_t content_length) {
    char header[MAX_BUFFER_SIZE];
    snprintf(header, sizeof(header),
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        status, content_type, content_length);
    
    send(client_socket, header, strlen(header), 0);
    if (content && content_length > 0) {
        send(client_socket, content, content_length, 0);
    }
}

static void send_error_page(SOCKET client_socket, const char* status, const char* error_page_path) {
    FILE* file = fopen(error_page_path, "rb");
    if (!file) {
        // Fallback to a simple error message if the custom error page is not found
        const char* fallback_error = "<h1>Error</h1>";
        send_http_response(client_socket, status, "text/html", fallback_error, strlen(fallback_error));
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = malloc(file_size);
    if (!content) {
        fclose(file);
        const char* error = "<h1>500 - Internal Server Error</h1>";
        send_http_response(client_socket, "500 Internal Server Error", "text/html", error, strlen(error));
        return;
    }

    fread(content, 1, file_size, file);
    fclose(file);

    send_http_response(client_socket, status, "text/html", content, file_size);
    free(content);
}

void process_file_request(SOCKET client_socket, const char* request_path) {
    char file_path[MAX_PATH_LENGTH] = "wwwroot";
    strcat(file_path, strcmp(request_path, "/") == 0 ? "/index.html" : request_path);

    FILE* file = fopen(file_path, "rb");
    if (!file) {
        send_error_page(client_socket, "404 Not Found", "wwwroot/error_pages/404.html");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = malloc(file_size);
    if (!content) {
        fclose(file);
        send_error_page(client_socket, "500 Internal Server Error", "wwwroot/error_pages/500.html");
        return;
    }

    fread(content, 1, file_size, file);
    fclose(file);

    send_http_response(client_socket, "200 OK", get_content_type(file_path), content, file_size);
    free(content);
}

void handle_client_request(SOCKET client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        char method[32], path[MAX_PATH_LENGTH], protocol[32];
        sscanf(buffer, "%s %s %s", method, path, protocol);
        
        if (strcmp(method, "GET") == 0) {
            process_file_request(client_socket, path);
        } else {
            send_error_page(client_socket, "501 Not Implemented", "wwwroot/error_pages/501.html");
        }
    }
}