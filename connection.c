#include "putty_network.h"
#include "putty_interface.h"

SOCKET global_client_socket;
SOCKET global_server_socket;

void init_win_socket()
{
    WSADATA wsaData;
    WORD version_requested = WVERSION_REQUESTED;

    if (WSAStartup(version_requested, &wsaData) != 0)
    {
        fprintf(stderr, "Error initializing Winsock.\n");
        exit(1);
    }
}

SOCKET create_socket()
{
    SOCKET new_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (new_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "Error creating the socket.\n");
        WSACleanup();
        exit(1);
    }
    return new_socket;
}

void bind_socket(SOCKET socket, struct sockaddr_in* addr)
{
    if (bind(socket, (struct sockaddr*)addr, sizeof(*addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Error binding the socket.\n");
        closesocket(socket);
        WSACleanup();
        exit(1);
    }
}

void listen_for_connections(SOCKET socket)
{
    if (listen(socket, 1) == SOCKET_ERROR)
    {
        fprintf(stderr, "Error in listening socket.\n");
        closesocket(socket);
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

void connect_to_server(SOCKET client_socket, struct sockaddr_in* server_addr)
{
    if (connect(client_socket, (struct sockaddr*)server_addr, sizeof(*server_addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Connection error.\n");
        closesocket(client_socket);
        WSACleanup();
        exit(1);
    }
}

void establish_connection(uint8_t is_server)
{
    init_win_socket();

    if (is_server)
    {
        global_server_socket = create_socket();
        struct sockaddr_in server_addr;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(PORT);

        bind_socket(global_server_socket, &server_addr);

        listen_for_connections(global_server_socket);

        global_client_socket = accept_client_connection(global_server_socket);
    }
    else
    {
        global_client_socket = create_socket();
        struct sockaddr_in server_addr;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(PORT);

        connect_to_server(global_client_socket, &server_addr);
    }
}

void close_connection()
{
    closesocket(global_client_socket);
    closesocket(global_server_socket);
    WSACleanup();
}
