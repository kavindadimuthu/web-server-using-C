// include/http_handler.h
#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include <winsock2.h>

#define MAX_BUFFER_SIZE 4096
#define MAX_PATH_LENGTH 2048

void handle_client_request(SOCKET client_socket);
void process_file_request(SOCKET client_socket, const char* request_path);

#endif