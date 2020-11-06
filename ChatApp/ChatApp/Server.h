#pragma once
#include "Includes.h"
extern int client, server;
extern char buffer[1024];
extern struct sockaddr_in server_addr;
extern int port;
extern bool Stop;
extern std::string msg;
extern int size;
int init_socket();
int bind_the_socket();
int listen_a_accept();