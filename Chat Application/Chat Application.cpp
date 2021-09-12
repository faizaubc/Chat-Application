// Chat Application.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h> //windows sockets uses this api to access the network
//it includes winsock network
#pragma comment (lib, "ws2_32.lib") //tells the linker to add the 'libname' library to the list
//of library dependencies as if you had added it in the project properties at Linker -> 
//Input-> Additional dependencies
using namespace::std;

int main()
{
    cout << "Hello World  !!\n";
	//initialize winsock = windows socket
	WSADATA wsData;

	//create a socket one thta we are binding to
	//creating a socket has a domain IPv4 protocol or IPv6 protocol
	//The IPv6 is the sixth revision to the Internet Protocol and sucessor to IPv4
	//It provides unique addresses necessary for internet-enabled devices to communicate
	//It also asks for a socket type: the communication type 

	//bind the socket to an ip address and port

	//wait for a connectionn

	//close listening socket

	//while loop: accept and echo message back to client

	//close the socket

	//shutdown winsock
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
