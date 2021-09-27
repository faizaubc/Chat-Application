// Chat Application.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h> //windows sockets uses this api to access the network
//it includes winsock network
#pragma comment (lib, "ws2_32.lib") //tells the linker to add the 'libname' library to the list
//of library dependencies as if you had added it in the project properties at Linker -> 
//Input-> Additional dependencies
using namespace::std;
void main()
{
	printf("gi");
	cout << "Hello World  !!\n";
	//initialize winsock = windows socket
	WSADATA wsData;
	//The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2
	//of Winsock on the system, and sets the passed version as the highest version
	//of Windows Sockets support that the caller can use.
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);

	if (wsok != 0)
	{
		cerr << "cant initialize winsock ! Quitting" << endl;
		return;
	}


	//create a socket one thta we are binding to
	//creating a socket has a domain IPv4 protocol or IPv6 protocol
	//The IPv6 is the sixth revision to the Internet Protocol and sucessor to IPv4
	//It provides unique addresses necessary for internet-enabled devices to communicate
	//It also asks for a socket type: the communication type 
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	//AF_INET is used to specify the IPv4 address family.
	//	SOCK_STREAM is used to specify a stream socket.
	//IPPROTO_TCP is used to specify the TCP protocol 

	if (listening == INVALID_SOCKET)
	{
		cerr << "Cant create a socket ! Quitting" << endl;
		return;
	}
	//bind the socket to an ip address and port
	//link the ip address and the port to the socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(22);//htons= host to network shorts use port 5  4000
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	//we are binding the port 54000 to any address
	bind(listening, (sockaddr*)&hint, sizeof(hint));


	//tell the winsock socket is for listening
	listen(listening, SOMAXCONN);
	//somaxconn=maximum connections we can have is large

	//wait for a connectionn
	sockaddr_in client;
	int clientSize = sizeof(client);

	//socket we are listening in on is bound to 54000
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Cant create a socket ! Quitting" << endl;
		return;
	}


	char host[NI_MAXHOST];//client remote name
	char service[NI_MAXHOST];//service (ie port ) the client is connected on 

	//zero memory the service and the host
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);//fills the memory with zero 

	//try and look up the host name client is connected to 
	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST,
		service, NI_MAXSERV, 0) == 0)
	{
		cout << host << "connected on port " << service << endl;
	}//or else get the port number
	else {
		//IP address and port
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);//grab the port 
		cout << host << "connected on port " <<
			ntohs(client.sin_port) //network to host short
			<< endl;
	}

	//close listening socket
	closesocket(listening);

	//while loop: accept and echo message back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		//wait for client to send data
		int byteReceived = recv(clientSocket, buf, 4096, 0);
		if (byteReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (byteReceived == 0)
		{
			cout << "Client is disconnected " << endl;
			break;
		}

		//echo message back to client

		send(clientSocket, buf, byteReceived + 1, 0);

	}

	//close the socket
	closesocket(clientSocket);

	//shutdown winsock
	WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging me nu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
