#!/usr/bin/python           # This is dropbin-client.py file

import sys
import socket
import os
import time

def validate_args(argv):    
    if (len(sys.argv) != 4):
        print "Usage : python dropbin-client.py <server-ip> <server-port> <user>"
        sys.exit(1)
     
def transferFiles(c_socket, dir_path, files_list):
    for item in files_list:   # Loop through files in directory
        c_socket.send('f_con')
        
        c_socket.send(item) # Send file name to server
        c_socket.recv(5)  # Recv Ack msg
        
        with open(dir_path +item, 'rb') as f:
            data = f.read(1024) 
            while (data):
                c_socket.send('d_con')
                c_socket.send(data)     # Send data to server
                c_socket.recv(5)    # Recv Ack msg
                data = f.read(1024)
            c_socket.send('f_sen')   # Send Ack msg
    c_socket.send('f_all')  # Send Ack msg

def removeFiles(c_socket, files_removed):
    for item in files_removed:
        c_socket.send('f_con')  # Ack msg
        c_socket.send(item) # Send file name to server
        c_socket.recv(5)    # Recv Ack msg
    c_socket.send('f_all')  # Send Ack msg

validate_args(sys.argv) # Validates the provided arguments

server_addr = (sys.argv[1], int(sys.argv[2]))   # Initialize Server Info
client_id = sys.argv[3]     # Initialize Client Id
dir_path = "dropbin_client/"    # Initialize Directory Path
dir_list = os.listdir(dir_path) # Initialize Directory List

c_socket = socket.socket()  # Creates a socket
c_socket.connect(server_addr) # Connects with the server

print c_socket.recv(1024) # Recieve welcome message
c_socket.send(client_id)    # Send client id to the server
print 'How can I serve you ' + client_id

transferFiles(c_socket, dir_path, dir_list)

files_before = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path)])
while True:
    time.sleep(8)
    files_after = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path)])
    
    files_added = []
    files_added = [item for item in files_after if not item in files_before]
    
    files_removed = []
    files_removed = [item for item in files_before if not item in files_after]
    
    files_updated = []
    files_updated = [item for item in files_after if item in files_before and files_before[item] != files_after[item]]
    
    if (files_added or files_updated):
        c_socket.send('f_add')  # Send Ack msg
        files_list = files_added + files_updated
        transferFiles(c_socket, dir_path, files_list)
        
    if (files_removed):
        c_socket.send('f_rem')  # Send Ack msg
        removeFiles(c_socket, files_removed)
        
    c_socket.send('fnext')  # Send Ack msg        
    
    files_before = files_after 

c_socket.close()    # Close the socket when done
 
