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
#include <dirent.h>
#include <iostream>
#include <cstring>
#include <fstream>

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
string getCurrentDir(void);
bool isExists(string filename);
bool createFile(string filename);

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
		
		bool flag = true;
		
		do
		{
			clearBuffer(buff);
			recvMessage(c_sock_fd, buff, 4);
			
			if (strncmp(buff, "list", 4) == 0)
			{
				string file_list = getCurrentDir();
				
				clearBuffer(buff);
				strcpy(buff, file_list.c_str());

				sendMessage(c_sock_fd, buff, strlen(buff));

				cout << "\nSending file list ....\n\n";
			}
			else if (strncmp(buff, "_noA", 4) == 0)
			{
				// do nothing
			}	
			else if (strncmp(buff, "_cre", 4) == 0)
			{
				clearBuffer(buff);
				recvMessage(c_sock_fd, buff, BUFFER_SIZE);

				string filename = buff;
				
				if (isExists(filename))
				{
					clearBuffer(buff);
					string ack = "Server: The file '" + filename + "' already exists.";
					strcpy(buff, ack.c_str());
					sendMessage(c_sock_fd, buff, strlen(buff));
				}
				else
				{
					if (createFile(filename))
					{
						clearBuffer(buff);
						string ack = "Server: The file '" + filename + "' has been created.";
						strcpy(buff, ack.c_str());
						sendMessage(c_sock_fd, buff, strlen(buff));	
					}
					else
					{
						clearBuffer(buff);
						string ack = "Server: File Creation Failed!\n";
						strcpy(buff, ack.c_str());
						sendMessage(c_sock_fd, buff, strlen(buff));		
					}
					
				}
			}
			else if (strncmp(buff, "exit", 4) == 0)
			{
				flag = false;
			}
			else
			{
				clearBuffer(buff);
				string helpMsg = "\n> Invalid Command\n> HELP : \n\n> LIST server\n> LIST client\n> exit\n\n";
				strcpy(buff, helpMsg.c_str());
				
				sendMessage(c_sock_fd, buff, strlen(buff));

				cout << "c: invalid command\n"
					<< "Sending help...\n\n";
			}

		} while (flag);

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
	int x = write(sock_id, "Hello from this side of the world", 33);
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
	cout << "\nA new client connected to server...\n\n";
}

void printClientDisconnect(void)
{
	cout << "\nClient Disconnected...\n\n"
		<< "Listening to clients again... \n\n";
}

string getCurrentDir(void)
{
	string file_list = "\n> Server : File List\n";
	DIR *_dir;
	struct dirent *_files;

	_dir = opendir("./");
	if (_dir != NULL)
	{
		while (_files = readdir(_dir))
		{
			file_list += "> ";
			file_list += _files->d_name;
			file_list += "\n";
		}
	}

	return file_list;
}

bool isExists(string filename)
{

	ifstream in_file;
	in_file.open(filename.c_str());
	if (in_file.fail())
	{
		return false;
	}
	
	in_file.close();
	return true;
}

bool createFile(string filename)
{
	ofstream of_file;
	of_file.open(filename.c_str());
	if (of_file.fail())
	{
		return false;
	}
	
	of_file.close();
	return true;
}













