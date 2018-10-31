#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 256

// prototype
void checkParameters(int argc, char *argv[]);
int openSocket(void);
void bindSocket(int sock_id, struct sockaddr_in srv_ad);
int acceptConn(int s_sock_id, struct sockaddr_in cli_ad);
void recvMessage(int sock_id, char buff[], int buff_size);
void sendMessage(int sock_id, char buff[], int buff_size);
void clearBuffer(char buff[]);
void sendHello(int sock_id);
void printWelcome(int port);
void printAccept(struct sockaddr_in cli_ad);
void printClientDisconnect(void);
bool isExit(char buff[]);

int main(int argc, char *argv[])
{
	// variable definitions
	int s_sock_fd, c_sock_fd, port;
	socklen_t clilen;
	struct sockaddr_in srv_ad, cli_ad;
	char buff[BUFFER_SIZE];

	checkParameters(argc, argv);	// check parameters

	port = atoi(argv[1]);	// getting port no.

	s_sock_fd = openSocket();	// open socket

	// server details
	srv_ad.sin_family = AF_INET;
	srv_ad.sin_addr.s_addr = INADDR_ANY;
	srv_ad.sin_port = htons(port);

	bindSocket(s_sock_fd, srv_ad);	// binding socket

	printWelcome(port);

	listen(s_sock_fd, 5);	// starts listening for clients

	while (true)
	{
		c_sock_fd = acceptConn(s_sock_fd, cli_ad);	// accepting connection from client

		printAccept(cli_ad);

		sendHello(c_sock_fd);
		
		do
		{
			clearBuffer(buff);
			cout << "c : ";
			recvMessage(c_sock_fd, buff, BUFFER_SIZE);
			cout << buff << endl;

		} while (isExit(buff));

		printClientDisconnect();

		close(c_sock_fd);	
	}
	
	close(s_sock_fd);
	return 0;

}

void checkParameters(int argc, char* argv[])
{
	if (argc != 2)
    {
      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
      exit(-1);
    }
}

int openSocket(void)
{
	int sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_id < 0)
	{
		cout << "Error : Opening Socket\n";
		exit(-1);
	}
	return sock_id;
}

void bindSocket(int sock_id, struct sockaddr_in srv_ad)
{
	int srv_size = sizeof(srv_ad);
	if (bind(sock_id, (struct sockaddr *) &srv_ad, srv_size) < 0)
	{
		cout << "Error : Binding Socket\n";
		exit(-1);
	}
}

int acceptConn(int s_sock_id, struct sockaddr_in cli_ad)
{
	socklen_t clilen;
	clilen = sizeof(cli_ad);

	int c_sock_id = accept(s_sock_id, (struct sockaddr *) &cli_ad, &clilen);
	if (c_sock_id < 0)
	{
		cout << "Error : Accepting Connection\n";
		exit(-1);
	}	
	return c_sock_id;
}

void recvMessage(int sock_id, char buff[], int buff_size)
{
	int x = read(sock_id, buff, buff_size);
	if (x < 0)
	{
		cout << "Error : reading from socket failed\n";
		exit(-1);
	}
}

void sendMessage(int sock_id, char buff[], int buff_size)
{
	int x = write(sock_id, buff, buff_size);
	if (x < 0)
	{
		cout << "Error : writing to socket failed\n";
		exit(-1);
	}
}

void clearBuffer(char buff[])
{
	bzero(buff, BUFFER_SIZE);
}

void sendHello(int sock_id)
{
	int x = write(sock_id, "Hello from this of the world", 28);
	if (x < 0)
	{
		cout << "Error : writing to socket failed\n";
		exit(-1);
	}	
}

void printWelcome(int port)
{
	cout << "\nStarting to run server at port " << port
		<< "\n.. creating local listener socket\n"
		<< ".. binding socket to port:"<< port
		<< "\n.. starting to listen at the port\n"
		<< ".. waiting for connection \n\n";
}

void printAccept(struct sockaddr_in cli_ad)
{
	cout << "\nClient connected to server...\n\n";
}

void printClientDisconnect(void)
{
	cout << "\nBrother please don't go...\n\n"
		<< "Listening to clients again... \n\n";
}

bool isExit(char buff[])
{
	for (int i = 0; buff[i]; i++)
	{
		buff[i] = tolower(buff[i]);
	}

	if (strncmp(buff, "exit", 4) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


















