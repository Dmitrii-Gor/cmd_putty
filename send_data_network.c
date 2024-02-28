#include "putty_network.h"
#include "putty_interface.h"


void send_messages()
{
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        send(global_client_socket, buffer, strlen(buffer), 0);
    }
}


void send_data()
{
    send_messages();
}
