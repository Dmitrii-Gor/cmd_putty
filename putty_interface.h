#ifndef PUTTY_INTERFACE_H_INCLUDED
#define PUTTY_INTERFACE_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <pthread.h>

void send_data();
void receive_data(uint8_t is_server);
void establish_connection(uint8_t is_server);
void close_connection();

#endif // PUTTY_INTERFACE_H_INCLUDED
