#define _WIN32_WINNT 0x501

/*
This software is a deliberately vulnerable threaded TCP server application

This is vulnerable software, don't run it on an important system!  The author assumes no responsibility if 
you run this software and your system gets compromised, because this software was designed to be exploited!

Forked and modified by Fortunato Lodari fox@thebrain.net (foxlox)  starting by Vulnserver sources, wrote by Stephen Bradsh in 2010.

Original Copyright (c) 2010, Stephen Bradshaw
All rights reserved.

*/

#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define VERSION "1.00"
#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "23"


void Function1(char *Input);
void Function2(char *Input);
void Function3(char *Input);
void Function4(char *Input);
DWORD WINAPI ConnectionHandler(LPVOID CSocket);


int main( int argc, char *argv[] ) {
	char PortNumber[6];
	const char Usage[94] = "Usage: %s [port_number]\n\nIf no port number is provided, the default port of %s will be used.\n";
	if ( argc > 2) {
		printf(Usage, argv[0], DEFAULT_PORT);
		return 1;
	} else if ( argc == 2 ) {
		if ( (atoi(argv[1]) > 0) && (atoi(argv[1]) < 65536) && (strlen(argv[1]) < 7) ) {
			strncpy(PortNumber, argv[1], 6);
		} else {
			printf(Usage, argv[0], DEFAULT_PORT);
			return 1;
		}
	} else {		
		strncpy(PortNumber, DEFAULT_PORT, 6);
	}
	printf("Starting vulnerable software (BOF)\n", VERSION);
	auxfunc1(); // Call function from external dll
	printf("\nThis is vulnerable software!\nDo not allow access from untrusted systems or networks!n\n");
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET,
	ClientSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, hints;
	int Result;
	struct sockaddr_in res1,ClientAddress;
	int ClientAddressL = sizeof(ClientAddress);

	Result = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (Result != 0) {
		printf("WSAStartup failed with error: %d\n", Result);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	Result = getaddrinfo(NULL, PortNumber, &hints, &result);
	if ( Result != 0 ) {
		printf("Getaddrinfo failed with error: %d\n", Result);
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
//	res1.sin_family = AF_INET;
//     	res1.sin_addr.s_addr = inet_addr("127.0.0.1");
//	res1.sin_port=htons(23);
	Result = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//	Result = bind( ListenSocket, (struct sockaddr *)&res1, sizeof(res1));
	if (Result == SOCKET_ERROR) {
		printf("Bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	Result = listen(ListenSocket, SOMAXCONN);
	if (Result == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}		
	while(ListenSocket) {	
		printf("Waiting for client connections...\n");

		ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddress, &ClientAddressL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("Accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		printf("Received a client connection from %s:%u\n", inet_ntoa(ClientAddress.sin_addr), htons(ClientAddress.sin_port));
		CreateThread(0,0,ConnectionHandler, (LPVOID)ClientSocket , 0,0);
		
	}

	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}


void f1(char *Input) {
	char Buffer2S[140];
	strcpy(Buffer2S, Input);
}

void f2(char *Input) {
	char Buffer2S[60];
	strcpy(Buffer2S, Input);
}

void f3(char *Input) {
	char Buffer2S[1890];	
	strcpy(Buffer2S, Input);
}

void f4(char *Input) {
	char Buffer2S[1000];
	strcpy(Buffer2S, Input);
}


DWORD WINAPI ConnectionHandler(LPVOID CSocket) {
	int RecvBufLen = DEFAULT_BUFLEN;
	char *RecvBuf = malloc(DEFAULT_BUFLEN);
	char BigEmpty[1000];
	char *GdogBuf = malloc(1024);
	int Result, SendResult, i, k;
	memset(BigEmpty, 0, 1000);
	memset(RecvBuf, 0, DEFAULT_BUFLEN);
	SOCKET Client = (SOCKET)CSocket; 
	SendResult = send( Client, "Verification Code:\n", 20, 0 );
	if (SendResult == SOCKET_ERROR) {
		//printf("Send failed with error: %d\n", WSAGetLastError());
		closesocket(Client);
		return 1;
	}
	while (CSocket) {
		Result = recv(Client, RecvBuf, RecvBufLen, 0);
		if (Result > 0) {
				char *TrunBuf = malloc(2900);
				memset(TrunBuf, 0, 2900);
				strncpy(TrunBuf, RecvBuf, 2900);
				for (int k=0;k<strlen(TrunBuf);k++)
				{
					if ((TrunBuf[k]==77)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
					if ((TrunBuf[k]==79)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
					if ((TrunBuf[k]==95)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
					if ((TrunBuf[k]==121)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
					if ((TrunBuf[k]==126)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
					if ((TrunBuf[k]==127)) {TrunBuf[k+1]='\0';TrunBuf[k]=176;}
				}
				f3(TrunBuf);
				memset(TrunBuf, 0, 2900);				

				//SendResult = send(Client, "Wrong Code!\n", 14, 0 );
				closesocket(Client);
				
				return 0;
			}
			if (SendResult == SOCKET_ERROR) {
				//printf("Send failed with error: %d\n", WSAGetLastError());
				closesocket(Client);
				return 1;
			}
			
		}

	}


void aauxfunc4() {
	__asm__("jmp *%esp\n\t"
		"jmp *%ebx\n\t"
		"pop %ebp\n\t"
		"pop %ebp\n\t"
		"ret");
}

