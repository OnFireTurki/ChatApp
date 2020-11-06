#include "Includes.h"
#include "Client.h"
#include "Server.h"
int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "Failed\tError code is" << WSAGetLastError() << std::endl;
		return 1;
	}
	std::cout << "Hello\n[1] - Create Sever\n[2] - Create Client\nChoose : ";
	int choose;
	std::cin >> choose;
	std::cin.ignore();
	if (choose == 1) {
		if (init_socket() == 0)
			if (bind_the_socket() == 0)
				listen_a_accept();
	}
	else {
		if (init_Client() == 0)
			client_connect();
	}
}