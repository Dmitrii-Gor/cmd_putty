#ifndef CMD_PUTTY_H_INCLUDED
#define CMD_PUTTY_H_INCLUDED

#include <winsock2.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define WVERSION_REQUESTED 0x0202
#define PORT 865


extern SOCKET global_client_socket;
extern SOCKET global_server_socket;

void init_win_socket();
SOCKET create_socket();
void bind_socket(SOCKET socket, struct sockaddr_in* addr);
void listen_for_connections(SOCKET socket);
SOCKET accept_client_connection(SOCKET server_socket);
void connect_to_server(SOCKET client_socket, struct sockaddr_in* server_addr);
void send_messages();
void receive_messages(uint8_t is_server);


#endif // CMD_PUTTY_H_INCLUDED
