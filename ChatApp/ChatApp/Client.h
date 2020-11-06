#pragma once
#include "Includes.h"
extern int client_;
extern char client_buffer[1024];
extern  struct sockaddr_in client_server_addr;
extern int client_port; // The port should be the same for client and sever
extern bool client_Stop;
extern std::string client_msg;
extern  std::string ip;
int init_Client();
int client_connect();