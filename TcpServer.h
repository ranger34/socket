#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

class TcpServer
{
private:
	int listenSock;
	int communicationSock;
	sockaddr_in servAddr;
	sockaddr_in clntAddr;
public:
	TcpServer(int listen_port);
	bool isAccept();
	void handleEcho();
};

#endif
