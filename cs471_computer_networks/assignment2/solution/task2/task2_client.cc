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

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define BUFFER_SIZE 256
// prototype
void checkParameters(int argc, char *argv[]);
int openSocket(void);
void connect2Server(int sock_id, struct sockaddr_in srv_ad);
struct hostent* getHostName(char* hostname);
void recvMessage(int sock_id, char buff[], int buff_size);
void sendMessage(int sock_id, char buff[], int buff_size);
void clearBuffer(char buff[]);
bool isExit(char buff[]);

int main(int argc, char *argv[])
{
  	// variable definitions
	int c_sock_fd, port;
	struct sockaddr_in srv_ad;
	struct hostent *serv;
	char buff[BUFFER_SIZE];

  	// check that there are enough parameters
 	checkParameters(argc, argv);

    port = atoi(argv[2]);	// getting port no.

	c_sock_fd = openSocket();	// open socket
	
	char *hostname = argv[1];	
	serv = getHostName(hostname);	// get hostname

	// server details
	srv_ad.sin_family = AF_INET;
	srv_ad.sin_port = htons(port);
	int serv_l = serv->h_length;
	bcopy((char *)serv->h_addr, (char *) &srv_ad.sin_addr.s_addr, serv_l);
	
	connect2Server(c_sock_fd, srv_ad);	// Connect to server

	clearBuffer(buff);
	
	recvMessage(c_sock_fd, buff, BUFFER_SIZE);

	cout << endl << buff << endl << endl;

	do
	{
		clearBuffer(buff);
		cout << "\nc : ";
		fgets(buff, BUFFER_SIZE, stdin);
		sendMessage(c_sock_fd, buff, strlen(buff));

	} while (isExit(buff));

	close(c_sock_fd);

  return 0;
}

void checkParameters(int argc, char* argv[])
{
	if (argc != 3)
    {
      fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
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

void connect2Server(int sock_id, struct sockaddr_in srv_ad)
{
	int srv_size = sizeof(srv_ad);
	if (connect(sock_id, (struct sockaddr *) &srv_ad, srv_size) < 0)
	{
		cout << "Error : connection failed\n";
		exit(-1);
	}
}

struct hostent* getHostName(char* hostname)
{
	struct hostent *serv;
	serv = gethostbyname(hostname);
	if (serv == NULL)
	{
		cout << "Error : host not available\n";
		exit(-1);
	}
	return serv;
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