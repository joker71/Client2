#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include<string>

#define DEFAULT_BUFLEN 512
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
using namespace std;

int main(int argc, char** argv)
{
	WSADATA wsaData;

	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	

	/*****************************************************/

	/*    Khoi tao Winsock 2.2
	/*****************************************************/
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	cout << "WSAStartup OK" << endl;
	/*****************************************************/
	/*    Creating a Socket for the Server: ListenSocket */
	/*****************************************************/
	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	cout << "ConnectSocket = socket OK" << endl;
	/*****************************************************/
	/*    Binding a Socket*/
	/*****************************************************/
	//Xac dinh dinh danh ung dung 
	int port = 81;
	const char* IP = "127.0.0.1";//"10.170.72.81"
	SOCKADDR_IN clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(port);
	clientAddr.sin_addr.s_addr = inet_addr(IP);

	if (connect(ConnectSocket, (SOCKADDR*)&clientAddr, clientAddrLen) == SOCKET_ERROR) {
		printf("\nCLIENT: Ket noi that bai\n");
		system("pause");
		WSACleanup();
	}
	else {
		printf("\nCLIENT: Ket noi thanh cong\n");
		printf("-----------------------------------------------------------------------\n");
	}
	//Gui nhan du lieu
	string myString;
	while (1) {
		//Nhap xau dau vao  
		cout << "\nNhap xau cua ban: ";
		//cin.ignore();
		getline(cin, myString);

		send(ConnectSocket, myString.c_str(), myString.size(), MSG_DONTROUTE);
		char connectedClient[256];
		recv(ConnectSocket, connectedClient, 256, 0);
		cout << "\nNhan tu server: " << connectedClient;
	}


	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}
