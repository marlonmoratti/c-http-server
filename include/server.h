#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>

typedef struct server {
    int socket_fd;
    struct sockaddr_in addr;
} Server;

/**
 * @brief Creates a server instance.
 * 
 * This function initializes a server instance by creating a socket.
 * 
 * @return The created server instance.
 */
Server create_server();

/**
 * @brief Binds the server to a specific IP address and port.
 * 
 * This function binds the server to a specific IP address and port.
 * 
 * @param server Pointer to the server instance.
 * @param ip_address IP address to bind to.
 * @param port Port number to bind to.
 */
void bind_server(Server *server, const char *ip_address, int port);

/**
 * @brief Listens for incoming connections on the server socket.
 * 
 * This function sets up the server to listen for incoming connections.
 * 
 * @param server Pointer to the server instance.
 */
void listen_connections(Server *server);

/**
 * @brief Accepts incoming client connections and handles them using the specified function.
 * 
 * This function continuously accepts incoming client connections
 * and spawns a new thread to handle each connection using the provided handler function.
 * 
 * @param server Pointer to the server instance.
 * @param handle_request Pointer to the function that handles client requests.
 *                       This function should have the same signature as 'void *(*handle_request)(void*)'.
 *                       It will be invoked with the client socket file descriptor as its argument.
 */
void accept_client_connections(Server *server, void *(*handle_request)(void*));

#endif
