#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define PORT 13 // port of daytime server

int main(int argc, char *argv[])
{
  // define your variables here
	int c_sock_fd, x;
	struct sockaddr_in srv_ad;
	struct hostent *serv;
	char buff[128];

  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydaytime <hostname>\n");
      exit(-1);
    }

  // Write your code here
	c_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (c_sock_fd < 0)
	{
		cout << "Error : Opening Socket\n";
		return 1;
	}

	char *hostname = argv[1];
	serv = gethostbyname(hostname);
	if (serv == NULL)
	{
		cout << "Error : host not available\n";
		return 1;
	}

	srv_ad.sin_family = AF_INET;
	srv_ad.sin_port = htons(PORT);
	int serv_l = serv->h_length;
	bcopy((char *)serv->h_addr, (char *) &srv_ad.sin_addr.s_addr, serv_l);

	int srv_size = sizeof(srv_ad);
	if (connect(c_sock_fd, (struct sockaddr *) &srv_ad, srv_size) < 0)
	{
		cout << "Error : connection failed\n";
		return 1;
	}

	bzero(buff, 128);
	x = read(c_sock_fd, buff, 128);
	if (x < 0)
	{
		cout << "Error : reading from socket failed\n";
		return 1;
	}
	cout << buff << endl;
	close(c_sock_fd);

  return 0;
}
