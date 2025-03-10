#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8080"
#define DEFAULT_BUFLEN 512

int __cdecl main(void) {

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	WSADATA wsaData;

	int iResult;

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		std::cout << "WSAStartup failed. " << iResult << std::endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

	if (iResult != 0) {
		std::cout << "getaddrinfo failed: " << iResult << std::endl;
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "Socket failed. " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

	if (iResult == SOCKET_ERROR) {
		std::cout << "Bind Failed with Error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);

	if (iResult == SOCKET_ERROR) {
		std::cout << "Listen() failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	ClientSocket = accept(ListenSocket, NULL, NULL);

	if (ClientSocket == INVALID_SOCKET) {
		std::cout << "accept failed: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	char request[DEFAULT_BUFLEN];

	iResult = recv(ClientSocket, request, DEFAULT_BUFLEN, 0);

	std::cout << request << std::endl;

	if (memcmp(request, "GET / ", 6) == 0) {

		FILE *f = fopen("index.html", "r");
		char buffer[DEFAULT_BUFLEN] = { 0 };
		fread(buffer, 1, DEFAULT_BUFLEN, f);
		std::string htmlContent = buffer;

		htmlContent = 
		"HTTP/1.0 200 OK \r\n"
		"Content-type: text/html\r\n\n" + htmlContent;

		send(ClientSocket, htmlContent.c_str(), htmlContent.size(), 0);

	}

	iResult = shutdown(ClientSocket, SD_SEND);

	if (iResult == SOCKET_ERROR) {

		std::cout << "Shutdown failed " << WSAGetLastError() << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
		return 1;

	}

	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}