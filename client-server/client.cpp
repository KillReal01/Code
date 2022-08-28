#include <iostream>
#include <thread>
#include <string>
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 1111
#define NETWORK "127.0.0.1"

class Client {
private:
	SOCKET client = INVALID_SOCKET;
	SOCKADDR_IN addr;
public:
	Client() {
		WSAData wsaData;
		int sizeofaddr = sizeof(addr);

		WORD DLLVersion = MAKEWORD(2, 1);
		if (WSAStartup(DLLVersion, &wsaData) != 0) {
			std::cout << "Error" << std::endl;
			exit(1);
		}
		inet_pton(AF_INET, NETWORK, &(addr.sin_addr));
		addr.sin_port = htons(PORT);
		addr.sin_family = AF_INET;
	}
	~Client() {
		closesocket(client);
		WSACleanup();
	}
	
	void start() {
		client = socket(AF_INET, SOCK_STREAM, NULL);
	}

	int connection() {
		return connect(client, (SOCKADDR*)&addr, sizeof(addr));
	}

	int receiving(char* msg) {
		return recv(client, msg, 256, NULL);
	}
};

Client sock;
const int SIZE_BUF = 32;
bool checkData(const std::string& buf);

void waiting(int& flag) {
	while (true) {
		if (flag == 0) {
			int connection = sock.connection();
			if (connection != 0) {// 0 - подключено
				std::cout << "error: failed connect to server\n";
				Sleep(2000);
			}
			else {
				std::cout << "connected to server\n";
				flag = 1;
			}
		}
	}
}

void working(int& flag) {
	char msg[256];
	while (true) {
		if (flag == 1) {
			int recieve = sock.receiving(msg);
			if (recieve != -1) {//-1 - не принят
				std::string buf(msg);
				if (checkData(buf)) {
					std::cout << "the data recieved\n";
				}
				else {
					std::cout << "error data\n";
				}
			}
			else {
				sock.start();
				flag = 0;
			}
		}
	}
}

int main() {
	int flag = 0;//0 - waiting, 1 - working

	sock.start();
	std::thread t1(waiting, std::ref(flag));
	std::thread t2(working, std::ref(flag));

	t1.join();
	t2.join();
	return 0;
}

bool checkData(const std::string& buf) {
	int count = 0, ch;
	for (int i = 0; i < buf.size(); i++) {
		ch = buf[i] - '0';
		if (ch >= 0 && ch <= 9) {
			count++;
		}
	}
	count = (SIZE_BUF * 2 - count) / 2 + count;//цифры + буквы / 2
	return (count > 2 && count % SIZE_BUF == 0) ? true : false;
}

