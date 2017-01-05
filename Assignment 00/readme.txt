Assignment 00

Client:
usage : python dropbin-client.py <server ip> <server port> <username>
<server ip> : ip address of the server.
<server port> : port number on which the server script is running.
<username> : To identify the user on the server end.
Once you run the dropbin-client.py, it starts monitoring the folder "dropbin_client" (residing in the same directory as "dropbin-client.py") for changes.


Server:
usage : python dropbin-server.py <server port>
<server port> : port number on which you want to run the server script.
Once you run the dropbin-server.py, it waits for the client connections. On every connection, the server script makes a new folder using the username provided by the client, and start replicating the directory on the client side to the client's directory on server side.
 