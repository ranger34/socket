#include "TcpServer.h"
#include <cstring>

TcpServer::TcpServer(int listen_port)
{
	if((listenSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		throw "socket() failed";
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(listen_port);

	if(bind(listenSock, (sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	{
		throw "bind() failed";
	}

	if(listen(listenSock, 10) < 0)
	{
		throw "listen() failed";
	}
}

bool TcpServer::isAccept()
{
	unsigned int clntAddrLen = sizeof(clntAddr);
	if((communicationSock = accept(listenSock, (sockaddr*)&clntAddr, &clntAddrLen)) < 0)
		return false;
	else
	{
		std::cout << "Client(IP: " << inet_ntoa(clntAddr.sin_addr) << ") connected. \n";
		return true;
	}
}

void TcpServer::handleEcho()
{
	const int BUFFERSIZE = 32;
	char buffer[BUFFERSIZE];
	int recvMsgSize;
	bool go_on = true;

	while( go_on == true )
	{
		if((recvMsgSize = recv(communicationSock, buffer, BUFFERSIZE, 0)) < 0)
			throw "recv() failed";
		else
			if(recvMsgSize == 0)
				go_on = false;
			else
				if(send(communicationSock, buffer, recvMsgSize, 0) != recvMsgSize)
					throw "send() failed";			
	}

	close(communicationSock);
}
