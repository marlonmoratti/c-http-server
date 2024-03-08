#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../server/include/server.h"

void *handle_request(void *arg) {
    int client_socket_fd = *((int *) arg);

    char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>";
    send(client_socket_fd, response, strlen(response), 0);
    close(client_socket_fd);

    return NULL;
}

int main() {
    const char *ip_address = "0.0.0.0";
    int port = 8080;

    Server server = create_server();
    
    bind_server(&server, ip_address, port);
    listen_connections(&server);
    
    accept_client_connections(&server, handle_request);

    return 0;
}
