#include "cmd_putty.h"
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


void send_messages(SOCKET client_socket)
{
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        send(client_socket, buffer, strlen(buffer), 0);
    }
}


void init_win_socket()
{
    WSADATA wsaData;
    WORD version_requested = WVERSION_REQUESTED;

    if (WSAStartup(version_requested, &wsaData) != 0)
    {
        fprintf(stderr, "Error initializing Winsock.\n");
        return 1;
    }
}


void init_server_socket(SOCKET* server_socket, struct sockaddr_in* server_addr)
{
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*server_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "error creating the socket.\n");
        WSACleanup();
        exit(1);
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = INADDR_ANY;
    server_addr->sin_port = htons(865);

    if (bind(*server_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "error linking the socket.\n");
        closesocket(*server_socket);
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


void init_client_socket(SOCKET* client_socket)
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
