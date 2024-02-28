#include "putty_network.h"
#include "putty_interface.h"

void receive_messages(uint8_t is_server)
{
    char buffer[1024];
    int bytes_read;

    while ((bytes_read = recv(global_client_socket, buffer, sizeof(buffer), 0)) > 0)
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


void receive_data(uint8_t is_server)
{
    receive_messages(is_server);
}
