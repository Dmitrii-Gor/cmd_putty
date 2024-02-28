#include "putty_interface.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    uint8_t is_server = 0;

    if ( argc > 1 && strcmp(argv[1], "-s") == 0)
    {
        printf("Running as server\n");
        is_server = 1;
    }

    establish_connection(is_server);
    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_data, is_server);
    send_data();

    close_connection();
    return 0;
}
