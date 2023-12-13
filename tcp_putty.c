#include "tcp_putty.h"
#include <stdio.h>
#include <string.h>

void receive_messages(struct thread_args *args)
{
    char buffer[1024];
    int bytes_read;
    SOCKET socket = args->socket;
    int is_server = args->flag;

    while ((bytes_read = recv(socket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[bytes_read] = '\0';

        if(is_server == 1)
        {
            printf("Client: %s", buffer);
        }
        else
            printf("Server: %s", buffer);
    }
}

void initialize_server_socket(SOCKET* server_socket)
{
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*server_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "error creating the socket.\n");
        WSACleanup();
        exit(1);
    }
}

void bind_server_socket(SOCKET server_socket, struct sockaddr_in* server_addr)
{
    if (bind(server_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "error link socket.\n");
        closesocket(server_socket);
        WSACleanup();
        exit(1);
    }
}

void listen_for_connections(SOCKET server_socket)
{
    if (listen(server_socket, 1) == SOCKET_ERROR)
    {
        fprintf(stderr, "error in listening socket.\n");
        closesocket(server_socket);
        WSACleanup();
        exit(1);
    }
}

SOCKET accept_client_connection(SOCKET server_socket)
{
    SOCKET client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "Error accepting the connection.\n");
        closesocket(server_socket);
        WSACleanup();
        exit(1);
    }
    return client_socket;
}

void initialize_client_socket(SOCKET* client_socket)
{
    *client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*client_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "error creating the socket.\n");
        WSACleanup();
        exit(1);
    }
}

void connect_to_server(SOCKET client_socket, struct sockaddr_in* server_addr)
{
    if (connect(client_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "connection error.\n");
        closesocket(client_socket);
        WSACleanup();
        exit(1);
    }
}
