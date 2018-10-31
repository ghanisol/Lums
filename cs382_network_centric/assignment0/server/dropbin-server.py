#!/usr/bin/python           # This is dropbin-server.py file

import socket
import os
import sys
from threading import Thread

def validate_args(argv):
    if (len(sys.argv) != 2):
        print "Usage : python dropbin-server.py <server-port>"
        sys.exit(1)

def addFiles(c_conn, dir_path, client_id):
    while (not c_conn.recv(5) == 'f_all'):
        
        filename = c_conn.recv(1024)
        c_conn.send('f_rec')    # Send Ack msg
        
        with open(dir_path +client_id + '/' +filename, 'wb') as f:
            while not c_conn.recv(5) == 'f_sen':
                data = c_conn.recv(1024)
                c_conn.send('d_rec')    # Send Ack msg
                f.write(data)

def removeFiles(c_conn, dir_path, client_id):
    while (c_conn.recv(5) != 'f_all'):
        item = c_conn.recv(1024)
        c_conn.send('f_rec')    # Send Ack msg
        os.remove(dir_path +client_id + '/' +item)
       
def clientHandler(c_conn, dir_path):
    while True:
        c_conn.send('Thank you for connecting')
        client_id = c_conn.recv(1024)    # Get client id from the user
        if not os.path.exists(dir_path + client_id):
            os.mkdir(dir_path + client_id)  # Makes the client's directory

        addFiles(c_conn, dir_path, client_id)
            
       
        while True:
            op = c_conn.recv(5) # Recv op msg
            if (op == 'f_add'):
                addFiles(c_conn, dir_path, client_id)
            elif (op == 'f_rem'):
                removeFiles(c_conn, dir_path, client_id)
            else:
                continue

        c_conn.close()

validate_args(sys.argv)     # Validates the provided arguments

dir_path = 'dropbin_server/'    # Initialize Directory Path

s_socket = socket.socket()  # Creates a socket
server_addr = (socket.gethostname(), int(sys.argv[1]))
s_socket.bind(server_addr)  # Bind server to the port

threads = []

while True:
    s_socket.listen(5)                 # Now wait for client connection.
    c_conn, c_addr = s_socket.accept()  # Establish connection with client.
    newClient = Thread(target=clientHandler, args=(c_conn, dir_path, )) # Makes a new thread
    newClient.start()   # Starts the new thread
    threads.append(newClient)
    
