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

int main(int argc, char *argv[])
{

  	// check that there are enough parameters
  	if (argc != 2)
    	{
      		fprintf(stderr, "Usage: mydns <hostname>\n");
      		exit(-1);
    	}
	struct hostent *srv;

  	// Address resolution stage by using gethostbyname()
	srv = gethostbyname(argv[1]);
 	// Write your code here!
	if (srv == NULL)
	{
		cout << "Error : Resolving hostname\n";
		return 1; 
	}

  	// Print to standard output
	struct in_addr **ip_list = (struct in_addr **)srv->h_addr_list;

	for (int i = 0; ip_list[i] != NULL; i++)
	{
		cout << inet_ntoa(*ip_list[i]) << endl;
	}
  	return 0;
}
