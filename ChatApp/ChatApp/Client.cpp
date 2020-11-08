#include "Client.h"

int client_;
char client_buffer[1024] = { 0 };
struct sockaddr_in client_server_addr;
int client_port = 8888; // The port should be the same for client and sever
bool client_Stop = false;
std::string client_msg;
std::string ip = "127.0.0.1";

int init_Client() {
	client_ = socket(AF_INET, SOCK_STREAM, 0);
	if (client_ < 0)
	{
		std::cout << "Error in socket.\n";
		return -1;
	}
	client_server_addr.sin_family = AF_INET;
	client_server_addr.sin_port = htons(client_port);
	inet_pton(AF_INET, ip.c_str(), &(client_server_addr.sin_addr));
	return 0;
}

int client_connect() {
	std::cout << "Tryinn to connect the server." << std::endl;
	if (connect(client_, (struct sockaddr*)&client_server_addr, sizeof(client_server_addr)) == 0) {
		std::cout << "Connection to the server port number: " << client_port << std::endl;
	}
	else {
		return -1;
	}
	std::cout << "Connection has been confirmed\n";
	std::cout << "\nEnter $E to end the connection\n" << std::endl;
	int i;
	while (!client_Stop) {
		std::cout << "\nClient: ";
		std::getline(std::cin, client_msg);
		send(client_, client_msg.c_str(), client_msg.length(), 0);
		if (client_msg.compare("$E") == 0) {
			client_Stop = true;
			break;
		}
		std::cout << "From Server: ";
		while (!client_Stop) {
			memset(client_buffer, 0, sizeof(client_buffer));
			i = recv(client_, client_buffer, 1024, 0);
			if (i > 0) {
				std::cout << client_buffer << " ";
				if (strcmp(client_buffer, "$E") == 0) {
					client_Stop = true;
					break;
				}
				i = NULL;
				break;
			}
			else if (i == 0)
				std::cout << "Connection closing...\n";
                                client_Stop = true;
			else {
				std::cout << "recv failed with error:" << WSAGetLastError() << std::endl;
				client_Stop = true;
			}
		}
	};
	closesocket(client_);
	WSACleanup();
	return 0;
}
