#include "Server.h"

int client, server;
char buffer[1024] = { 0 };
struct sockaddr_in server_addr;
int port = 8888; // The port should be the same for client and sever
bool Stop = false;
std::string msg;
int size = sizeof(server_addr);

int init_socket() {
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0)
	{
		std::cout << "Error in socket.\n";
		return -1;
	}
	std::cout << "The server has been created successfully\n";
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);
	return 0;
}

int bind_the_socket() {
	if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
	{
		std::cout << "Error binding connection.\n";
		return -1;
	}
	size = sizeof(server_addr);
	std::cout << "Searching for clients.\n";
	return 0;
}

int listen_a_accept() {
	listen(client, 1);
	int clientCount = 1;
	server = accept(client, (struct sockaddr*)&server_addr, &size);
	if (server < 0)
		return -1; // std::cout << "Error on accepting.\n";
	std::cout << "Connected with the client number-" << clientCount << "" << std::endl;
	std::cout << "\nEnter $E to end the connection\n" << std::endl;
	int i;
	while (server > 0)
	{
		while (!Stop) {
			std::cout << "From Client: ";
			i = recv(server, buffer, 1024, 0);
			if (i > 0) {
				std::cout << buffer << " ";
				if (strcmp(buffer, "$E") == 0) {
					Stop = true;
					break;
				}
				i = NULL;
				break;
			}
		}
		while (!Stop) {
			std::cout << "\nServer: ";
			std::getline(std::cin, msg);
			send(server, msg.c_str(), msg.length(), 0);
			if (msg.compare("$E") == 0) {
				Stop = true;
				break;
			}
			while (!Stop) {
				memset(buffer, 0, sizeof(buffer));
				std::cout << "From Client: ";
				i = recv(server, buffer, 1024, 0);
				if (i > 0) {
					std::cout << buffer << " ";
					if (strcmp(buffer, "$E") == 0) {
						Stop = true;
						break;
					}
					i = NULL;
					break;
				}
				else if (i == 0)
					std::cout << "Connection closing...\n";
                                        Stop = true;
				else {
					std::cout << "recv failed with error:" << WSAGetLastError() << std::endl;
					Stop = true;
				}
			}
		};
		char ip_[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(server_addr.sin_addr), ip_, INET_ADDRSTRLEN);
		std::cout << "\nConnection Closed IP:" << ip_ << std::endl;
		closesocket(server);
		Stop = false;
		break;
	}
	closesocket(client);
	WSACleanup();
	return 0;
}
