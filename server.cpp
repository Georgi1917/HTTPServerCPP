#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <cstring>
#include <fstream>
#include <sstream>
#include "HTTPResponse.h"
#include "UrlRouter.h"
#include "app/urls.h"
#include "app/views.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8080"
#define DEFAULT_BUFLEN 512

bool endsWith( std::string const &fullString, std::string const &ending) {

	if (fullString.length() >= ending.length()) {

		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));

	} else return false;

}

HTTPResponse buildHttpResponse(char request[DEFAULT_BUFLEN]) {

	if (memcmp(request, "GET /favicon.ico", 16) == 0) {

		std::ifstream file("templates/404.html");
		std:: ostringstream contentStream;
		contentStream << file.rdbuf();
		std::string header = "HTTP/1.0 400 Not Found";
		std::string ctype = "Content-Type: text/html";
		
		return HTTPResponse(header, ctype, contentStream.str());

	}

	if (memcmp(request, "GET / ", 6) == 0) {

		std::ifstream file("templates/index.html");
		std::ostringstream contentStream;
		contentStream << file.rdbuf();
		std::string header = "HTTP/1.0 200 OK";
		std::string ctype = "Content-Type: text/html";
		
		return HTTPResponse(header, ctype, contentStream.str());

	}

	else {

		std::string str(request);
		std::string fileName = "";

		for (int i = str.find('/') + 1; i < str.size(); i++) {

			if (str[i] == ' ') break;
			else fileName += str[i];

		}

		std::ifstream file("templates/" + fileName);
		std::ostringstream contentStream;
		contentStream << file.rdbuf();

		if (contentStream.str() == "") {

			std::ifstream file("templates/404.html");

			contentStream << file.rdbuf();

			std::string header = "HTTP/1.0 400 Not Found";
			std::string ctype = "Content-Type: text/html";

			return HTTPResponse(header, ctype, contentStream.str());

		}

		std::string header = "HTTP/1.0 200 OK";
		std::string ctype;
		if (endsWith(fileName, ".css")) ctype = "Content-Type: text/css";
		else ctype = "Content-Type: text/html";

		return HTTPResponse(header, ctype, contentStream.str());

	}

}

int main() {

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

	std::cout << "Listening on Port: " << DEFAULT_PORT << "\n\n";

	while(1) {

		ClientSocket = accept(ListenSocket, NULL, NULL);

		if (ClientSocket == INVALID_SOCKET) {

			std::cout << "accept failed: " << WSAGetLastError() << std::endl;
			continue;

		}

		char request[DEFAULT_BUFLEN] = { 0 };

		iResult = recv(ClientSocket, request, DEFAULT_BUFLEN, 0);

		std::cout << request << "\n\n";

		if (iResult == 0) {

			std::cout << "Connection Closed" << std::endl;
			closesocket(ClientSocket);
			continue;

		}
		else if (iResult < 0) {

			std::cout << "Recv failed" << WSAGetLastError() << std::endl;
			continue;

		}

		AddingRoutes();

		HTTPResponse hr = buildHttpResponse(request);
		
		send(ClientSocket, hr.GetResponse().c_str(), hr.GetResponse().size(), 0);

		shutdown(ClientSocket, SD_SEND);
		closesocket(ClientSocket);

	}

	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}