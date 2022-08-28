#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <vector>
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 1111
#define NETWORK "127.0.0.1"

class Server {
private:
	SOCKET sListen;
	SOCKADDR_IN addr;
public:
	SOCKET client = INVALID_SOCKET;

	Server() {
		WSAData wsaData;
		WORD DLLVersion = MAKEWORD(2, 1);
		if (WSAStartup(DLLVersion, &wsaData) != 0) {
			std::cout << "Error" << std::endl;
			exit(1);
		}
		inet_pton(AF_INET, NETWORK, &(addr.sin_addr));
		addr.sin_port = htons(PORT);
		addr.sin_family = AF_INET;

		sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);
	}
	~Server() {
		closesocket(client);
		closesocket(sListen);
		WSACleanup();
	}

	void start() {
		client = socket(AF_INET, SOCK_STREAM, NULL);
	}

	int acceptance() {
		int sizeofaddr = sizeof(addr);
		return accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	}

	int sending(char* msg) {
		return send(client, msg, 256, NULL);
	}
};

Server sock;
const int SIZE_BUF = 64;
std::string sharedbuf;

bool checkString(const std::string& buf);
bool logic(char a, char b);
std::string exchange(std::string& buf);
void helper(std::string& buf, std::vector<int>& vec);
int calculate();

void get(int& flag) {//поток 1
	std::string buf;
	while (true) {
		if (flag == 0) {
			std::cin >> buf;
			if (checkString(buf)) {
				sharedbuf = exchange(buf);
				flag = 1;
			}
		}
	}
}

void handle(int& flag) {//поток 2
	while (true) {
		if (flag == 1) {
			std::string str = sharedbuf;
			int sum = calculate();
			sharedbuf = "";
			flag = 0;

			std::string tmp = std::to_string(sum);
			std::cout << "string: " << str << ", sum = " << sum << std::endl;

			char msg[256];
			strcpy_s(msg, tmp.c_str());
			sock.sending(msg);
		}
	}
}

void waiting() {
	while (true) {
		sock.client = sock.acceptance();
		if (sock.client == INVALID_SOCKET) {
			std::cout << "error: failed connect to client\n";
		}
		else {
			std::cout << "client connected\n";
		}
	}
}

int main() {
	int flag = 0;//0 - works 1st thread // 1 - works 2nd thread

	sock.start();
	std::thread t1(get, std::ref(flag));
	std::thread t2(handle, std::ref(flag));
	std::thread t3(waiting);

	t1.join();
	t2.join();
	t3.join();
	return 0;
}

bool checkString(const std::string& buf) {
	int count = 0, ch;
	for (int i = 0; i < buf.size(); i++) {
		ch = buf[i] - '0';
		if (ch < 0 || ch > 9)
			return false;
		count++;
	}
	return (count == SIZE_BUF) ? true : false;
}

std::string exchange(std::string& buf) {
	std::vector<int> vec;
	int ch;
	std::sort(buf.begin(), buf.end(), logic);
	for (int i = 0; i < buf.size(); i++) {
		ch = buf[i] - '0';
		if (ch % 2 == 0) {//четно
			vec.push_back(i);
		}
	}
	helper(buf, vec);
	return buf;
}

void helper(std::string& buf, std::vector<int>& vec) {
	int pos, size = SIZE_BUF + vec.size();
	std::string tmp(size, '0');

	for (int i = 0; i < buf.size(); i++) {
		tmp[i] = buf[i];
	}

	for (int i = 0; i < vec.size(); i++) {
		pos = vec[i] + i;
		for (int j = size - 1; j >= pos + 1; j--) {
			tmp[j] = tmp[j - 1];
		}
		tmp[pos] = 'K';
		tmp[pos + 1] = 'B';
	}
	buf = tmp;
}

int calculate() {
	int ch, sum = 0;
	for (int i = 0; i < sharedbuf.size(); i++) {
		ch = sharedbuf[i] - '0';
		if (ch >= 0 && ch <= 9) {
			sum += ch;
		}
	}
	return sum;
}

bool logic(char a, char b) {
	return (a > b) ? true : false;
}