#include "cmd_putty.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    init_win_socket();

    int is_server = 0;

    if ( argc > 1 && strcmp(argv[1], "-s") == 0)
    {
        printf("Running as server\n");
        is_server = 1;
    }

    if (is_server)
    {
        SOCKET server_socket;
        struct sockaddr_in server_addr;

        init_server_socket(&server_socket, &server_addr);

        listen_for_connections(server_socket);

        SOCKET client_socket = accept_client_connection(server_socket);

        struct thread_args data = {client_socket, 1};

        pthread_t receive_thread;
        pthread_create(&receive_thread, NULL, receive_messages, &data);

        send_messages(client_socket);

        closesocket(client_socket);
        closesocket(server_socket);
    }
    else
    {
        SOCKET client_socket;
        struct sockaddr_in server_addr;

        init_client_socket(&client_socket);

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(865);

        connect_to_server(client_socket, &server_addr);

        struct thread_args data = {client_socket, 0};

        pthread_t receive_thread;
        pthread_create(&receive_thread, NULL, receive_messages, &data);

        send_messages(client_socket);

        closesocket(client_socket);
    }

    WSACleanup();
    return 0;
}
