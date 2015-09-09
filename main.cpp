#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "TcpServer.h"

int echo_server(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	int mainRtn = 0;
	try{
		mainRtn = echo_server(argc, argv);
	} catch(const char* s)
	{
		perror(s);
		exit(EXIT_FAILURE);
	}

	return mainRtn;
}

int echo_server(int argc, char* argv[])
{
	int port;
	if(argc == 2)
		port = atoi(argv[1]);
	else
		port = 5000;

	TcpServer myServ(port);

	while(true)
	{
		if(myServ.isAccept() == true)
			myServ.handleEcho();
	}

	return 0;
}
