#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/server.h"

#define MAX_PENDING_CONNECTIONS 10

Server create_server() {
    Server server = { 0 };
    server.socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server.socket_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    server.addr.sin_family = AF_INET;    
    return server;
}

void bind_server(Server *server, const char *ip_address, int port) {
    server->addr.sin_addr.s_addr = inet_addr(ip_address);
    server->addr.sin_port = htons(port);

    if (bind(server->socket_fd, (struct sockaddr *)&server->addr, sizeof(server->addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void listen_connections(Server *server) {
    if (listen(server->socket_fd, MAX_PENDING_CONNECTIONS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", ntohs(server->addr.sin_port));
}

void accept_client_connections(Server *server, void *(*handle_request)(void*)) {
    int client_socket_fd;
    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);

    while (1) {
        if ((client_socket_fd = accept(server->socket_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addr_len)) < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New connection accepted\n");
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_request, (void *)&client_socket_fd);
        pthread_detach(thread_id);
    }
}
