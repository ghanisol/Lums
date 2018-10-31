#!/usr/bin/python		# This is dropbin-client.py file

import sys
import socket
import os
import time

def validate_args(argv):
	if (len(sys.argv) != 4):
		print "Usage : python dropbin-client.py <server-ip> <server-port> <user>"
		sys.exit(1)

def sendFile(c_socket, dir_path, filename):
	c_socket.send(filename)		# Send filename to server
	c_socket.recv(5)

	with open(dir_path + filename, 'rb') as f:
		data = f.read(1024)
		while (data):
			c_socket.send('d_con')
			c_socket.send(data)		# Send data to server
			c_socket.recv(5)	# Recv Ack msg
			data = f.read(1024)
		c_socket.send('f_sen')		# Send Ack msg

def pushFiles(c_socket, dir_path, files_list):
	for item in files_list:
		c_socket.send('f_con')
		sendFile(c_socket, dir_path, item)
	c_socket.send('f_all')

def sendRemoveFiles(c_socket, files_list):
	for item in files_list:
		c_socket.send('f_con')
		c_socket.send(item)
		c_socket.recv(5)
	c_socket.send('f_all')

def removeFiles(c_socket, dir_path):
    while (c_socket.recv(5) != 'f_all'):
        item = c_socket.recv(1024)
        c_socket.send('f_rec')    # Send Ack msg
        if os.path.isfile(dir_path + item):	
        	os.remove(dir_path + item)

def pullFiles(c_socket, dir_path):
	c_socket.send('pullF')

	while (not c_socket.recv(5) == 'f_all'):
		filename = c_socket.recv(1024)
		c_socket.send('f_rec')

		with open(dir_path + filename, 'wb') as f:
			while (not c_socket.recv(5) == 'f_sen'):
				data = c_socket.recv(1024)
				c_socket.send('d_rec')
				f.write(data)

def sendList(c_socket, files_list):
	c_socket.send('slist')
	c_socket.recv(5)
	for item in files_list:
		c_socket.send('l_con')
		c_socket.send(item)
		c_socket.recv(5)
		c_socket.send(str(files_list[item]))
		c_socket.recv(5)
	c_socket.send('l_all')

def recvList(c_socket, files_list):
	c_socket.recv(5)
	c_socket.send('a_rec')
	while (c_socket.recv(5) != 'l_all'):
		key = c_socket.recv(1024)
		c_socket.send('k_rec')
		value = c_socket.recv(1024)
		c_socket.send('v_rec')
		files_list[key] = value

def normalSync(c_socket, dir_path, files_private):
	c_socket.send('nsync')
	c_socket.recv(5)
	files_list = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path) if not item in files_private])
	sendList(c_socket, files_list)

	op = c_socket.recv(5)
	if (op == 'f_add'):
		pullFiles(c_socket, dir_path)

	op = c_socket.recv(5)
	if (op == 'f_rem'):
		removeFiles(c_socket, dir_path)

	files_added = {}
	files_removed = {}
	recvList(c_socket, files_added)
	recvList(c_socket, files_removed)

	if (files_added):
		c_socket.send('f_add')
		pushFiles(c_socket, dir_path, files_added)
	else:
		c_socket.send('n_add')

	if (files_removed):
		c_socket.send('f_rem')
		sendRemoveFiles(c_socket, files_removed)
	else:
		c_socket.send('n_rem')

def selectiveSync(c_socket, dir_path, files_private):
	c_socket.send('ssync')
	c_socket.recv(5)
	serverList = {}
	syncList = {}
	recvList(c_socket, serverList)

	for item in serverList:
		print item

	op = raw_input('Please make a file called "selectiveSync.dropbin" in you directory with the names of files you wish to sync, and enter 1 :')

	with open(dir_path + 'selectiveSync.dropbin', 'rb') as f:
		data = f.readline()
		while (data):
			data = data[:-1]
			syncList[data] = '1'
			data = f.readline()

	sendList(c_socket, syncList)

def selectSync(c_socket, dir_path, files_private):
	option = int(raw_input("\nPlease enter the sync method.\n Enter 0 for selective sync, or enter 1 for normal sync: "))
	if (option == 0):
		selectiveSync(c_socket, dir_path, files_private)
	elif (option == 1):
		normalSync(c_socket, dir_path, files_private) 

def watchDir(c_socket, dir_path, files_private):

	files_before = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path) if not item in files_private])
	
	while True:
		time.sleep(8)
		flag = 0
		files_after = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path) if not item in files_private])

		files_added = []
		files_removed = []
		files_updated = []

		files_added = [item for item in files_after if not item in files_before]
		files_removed = [item for item in files_before if not item in files_after]
		files_updated = [item for item in files_after if item in files_before and files_before[item] != files_after[item]]

		if (files_added or files_updated):
			c_socket.send('f_add')
			files_list = files_added + files_updated
			pushFiles(c_socket, dir_path, files_list)
			flag = 1
		else:
			c_socket.send('n_add')

		if (files_removed):
			c_socket.send('f_rem')
			sendRemoveFiles(c_socket, files_removed)
			flag = 1
		else:
			c_socket.send('n_rem')
		
		if (flag == 0):	
			op = c_socket.recv(5)
			if (op == 'f_add'):
				pullFiles(c_socket, dir_path)

			op = c_socket.recv(5)
			if (op == 'f_rem'):
				removeFiles(c_socket, dir_path)
				
		files_after = dict([(item, os.stat(dir_path + item)[8]) for item in os.listdir(dir_path) if not item in files_private])
		files_before = files_after

validate_args(sys.argv)

server_addr = (sys.argv[1], int(sys.argv[2]))
client_id = sys.argv[3]
dir_path = "./"
dir_list = os.listdir(dir_path)

c_socket = socket.socket()
c_socket.connect(server_addr)

print c_socket.recv(1024)
c_socket.send(client_id)
c_socket.recv(5)
print 'How can i serve you ' + client_id

files_private = ['dropbin-client.py', 'selectiveSync.dropbin']
new_dir_list = [item for item in dir_list if not item in files_private]

op = c_socket.recv(5)
if (op == 'n_usr'):
	pushFiles(c_socket, dir_path, new_dir_list)
elif (op == '_sync'):
	selectSync(c_socket, dir_path, files_private)


watchDir(c_socket, dir_path, files_private)

c_socket.close()