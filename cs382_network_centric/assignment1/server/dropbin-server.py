#!/usr/bin/python		# This is dropbin-server file

import socket
import os
import sys
import shutil
from threading import Thread

def validate_args(argv):
	if (len(sys.argv) != 2):
		print "Usage : python dropbin-server.py <server-port>"
		sys.exit(1)

def updateShareFile(dir_path, share_file, filename, user):
    if (share_file == 'ClientShare.dropbin'):
        filelist = {}
        readShare(dir_path, user, share_file, filelist)

        with open(dir_path + user + '/' + share_file, 'wb') as f:
            for item in filelist:
                if (item != filename):
                    f.write(item + ' ' + ' '.join(filelist[item]))

    elif (share_file == 'SharedFiles.dropbin'):
        filelist = {}
        readShare(dir_path, user, share_file, filelist)

        with open(dir_path + user + '/' + share_file, 'wb') as f:
            for item in filelist:
                if (item != filename):
                    f.write(item + ' ' + ' '.join(filelist[item]))


def replicateChanges(dir_path, client_id, filename, clientShare_list, sharedFiles_list, op):

    if (op == 'copy'):

        if filename in clientShare_list:
            for user in clientShare_list[filename]:
                shutil.copy(dir_path + client_id + '/' + filename, dir_path + user)

                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(filename + ' file_added\n')

        if filename in sharedFiles_list:
            for user in sharedFiles_list[filename]:
                shutil.copy(dir_path + client_id + '/' + filename, dir_path + user)


                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(filename + ' file_added\n')

                otherusers = {}
                readShare(dir_path, user, 'ClientShare.dropbin', otherusers)
                for otheruser in otherusers[filename]:
                    if otheruser != client_id:
                        shutil.copy(dir_path + client_id + '/' + filename, dir_path + otheruser)

                        with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                            f.write(filename + ' file_added\n')

    elif (op == 'remove'):

        if filename in clientShare_list:
            updateShareFile(dir_path, 'ClientShare.dropbin', filename, client_id)

            for user in clientShare_list[filename]:
                if os.path.isfile(dir_path + user + '/' + filename):
                    os.remove(dir_path + user + '/' + filename)
                updateShareFile(dir_path, 'SharedFiles.dropbin', filename, user)

                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(filename + ' file_removed\n')

        if filename in sharedFiles_list:
            updateShareFile(dir_path, 'SharedFiles.dropbin', filename, client_id)
            for user in sharedFiles_list[filename]:
                if os.path.isfile(dir_path + user + '/' + filename):
                    os.remove(dir_path + user + '/' + filename)
            
                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(filename + ' file_removed\n')

                otherusers = {}
                readShare(dir_path, user, 'ClientShare.dropbin', otherusers)
                for otheruser in otherusers[filename]:
                    if otheruser != client_id:
                        if os.path.isfile(dir_path + otheruser + '/' + filename):
                            os.remove(dir_path + otheruser + '/' + filename)
                        updateShareFile(dir_path, 'SharedFiles.dropbin', filename, otheruser)

                        with open(dir_path + otheruser + '/' + 'sharedLog.txt', 'a+') as f:
                            f.write(filename + ' file_removed\n')

                updateShareFile(dir_path, 'ClientShare.dropbin', filename, user)



def pullFiles(c_conn, dir_path, client_id, clientShare_list, sharedFiles_list):
    
    while (not c_conn.recv(5) == 'f_all'):
        
        filename = c_conn.recv(1024)
        c_conn.send('f_rec')    # Send Ack msg
        
        with open(dir_path +client_id + '/' + filename, 'wb') as f:
            while (not c_conn.recv(5) == 'f_sen'):
                data = c_conn.recv(1024)
                c_conn.send('d_rec')    # Send Ack msg
                f.write(data)
        
        replicateChanges(dir_path, client_id, filename, clientShare_list, sharedFiles_list, 'copy')
        

def removeFiles(c_conn, dir_path, client_id, clientShare_list, sharedFiles_list):
    while (c_conn.recv(5) != 'f_all'):
        item = c_conn.recv(1024)
        c_conn.send('f_rec')    # Send Ack msg
        if os.path.isfile(dir_path + client_id + '/' + item):
            os.remove(dir_path +client_id + '/' + item)

        replicateChanges(dir_path, client_id, item, clientShare_list, sharedFiles_list, 'remove')
 
def readShare(dir_path, client_id, share_file, share_list):
    with open(dir_path + client_id + '/' + share_file, 'rb') as f:
        data = f.readline()
        while(data):
            temp = data.split()
            key = temp[0]
            temp.remove(key)
            share_list[key] = temp
            data = f.readline()      

def shareFiles(clientShare_before, clientShare_after, client_id):
    files_added = []
    files_removed = []
    users_changed = []

    files_added = [item for item in clientShare_after if not item in clientShare_before]
    files_removed = [item for item in clientShare_before if not item in clientShare_after]
    users_changed = [item for item in clientShare_after if item in clientShare_before and clientShare_after[item] != clientShare_before[item]]
    
    if (files_added):
        for item in files_added:
            for user in clientShare_after[item]:
                shutil.copy(dir_path + client_id + '/' + item, dir_path + user) 
                
                with open(dir_path + user + '/' +'SharedFiles.dropbin', 'a+') as f:
                    f.write(item + ' ' + client_id + '\n')
                    
                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(item + ' file_added\n')
                    
    if (files_removed):
        for item in files_removed:
            for user in clientShare_before[item]:
                
                if os.path.isfile(dir_path + user + '/' + item):
                    os.remove(dir_path + user + '/' + item)

                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(item + ' file_removed\n')

                updateShareFile(dir_path, 'SharedFiles.dropbin', item, user)

    if (users_changed):
        for item in users_changed:
            users_added = []
            users_added = [user for user in clientShare_after[item] if not user in clientShare_before[item]]
            for user in users_added:
                shutil.copy(dir_path + client_id + '/' + item, dir_path + user) 
                
                with open(dir_path + user + '/' +'SharedFiles.dropbin', 'a+') as f:
                    f.write(item + ' ' + client_id + '\n')

                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(item + ' file_added\n')

            users_removed = []
            users_removed =[user for user in clientShare_before[item] if not user in clientShare_after[item]]
            for user in users_removed:
                if os.path.isfile(dir_path + user + '/' + item):
                    os.remove(dir_path + user + '/' + item)
                updateShareFile(dir_path, 'SharedFiles.dropbin', item, user)

                with open(dir_path + user + '/' + 'sharedLog.txt', 'a+') as f:
                    f.write(item + ' file_removed\n')

def pushFiles(c_conn, dir_path, client_id, files_list):
    c_conn.recv(5)
    for item in files_list:   # Loop through files in directory
        c_conn.send('f_con')
        
        c_conn.send(item) # Send file name to server
        c_conn.recv(5)  # Recv Ack msg
        
        with open(dir_path + client_id + '/' + item, 'rb') as f:
            data = f.read(1024) 
            while (data):
                c_conn.send('d_con')
                c_conn.send(data)     # Send data to server
                c_conn.recv(5)    # Recv Ack msg
                data = f.read(1024)
            c_conn.send('f_sen')   # Send Ack msg
    c_conn.send('f_all')  # Send Ack msg

def pushChanges(serverFiles_after, serverFiles_before, c_conn, client_id, dir_path):

    files_added = []
    files_removed = []
    files_updated = []
    
    files_added = [item for item in serverFiles_after if not item in serverFiles_before]
    files_removed = [item for item in serverFiles_before if not item in serverFiles_after]
    files_updated = [item for item in serverFiles_after if item in serverFiles_before and serverFiles_before[item] != serverFiles_after[item]]

    if (files_added or files_updated):
        c_conn.send('f_add')
        files_list = files_added + files_updated
        pushFiles(c_conn, dir_path, client_id, files_list)
    else:
        c_conn.send('n_add')

    if (files_removed):
        c_conn.send('f_rem')
        sendRemoveFiles(c_conn, files_removed)
    else:
        c_conn.send('n_rem')   
       
def sendRemoveFiles(c_conn, files_list):
    for item in files_list:
        c_conn.send('f_con')
        c_conn.send(item)
        c_conn.recv(5)
    c_conn.send('f_all')

def updateLogFile(dir_path, client_id):
    logfile = 'logfile.txt'
    files_private = ['SharedFiles.dropbin', 'ClientShare.dropbin', 'logfile.txt', 'sharedLog.txt']
    files_list = dict([(item, os.stat(dir_path + client_id + '/' + item)[8]) for item in os.listdir(dir_path + client_id) if not item in files_private])
    with open(dir_path + client_id + '/' + logfile, 'wb') as f:
        for item in files_list:
            f.write(item + ' ' + str(files_list[item]) + '\n')

def sendList(c_conn, files_list):
    c_conn.send('slist')
    c_conn.recv(5)
    for item in files_list:
        c_conn.send('l_con')
        c_conn.send(item)
        c_conn.recv(5)
        c_conn.send(str(files_list[item]))
        c_conn.recv(5)
    c_conn.send('l_all')

def recvList(c_conn, files_list):
    c_conn.recv(5)
    c_conn.send('a_rec')
    while (c_conn.recv(5) != 'l_all'):
        key = c_conn.recv(1024)
        c_conn.send('k_rec')
        value = int(c_conn.recv(1024))
        c_conn.send('v_rec')
        files_list[key] = value

def normalSync(c_conn, client_id, dir_path, files_private):
    clientFiles = {}
    recvList(c_conn, clientFiles)
    
    sharedLog = {}
    logFile = {}
    readShare(dir_path, client_id, 'sharedLog.txt', sharedLog)
    readShare(dir_path, client_id, 'logfile.txt', logFile)

    files_updated = [item for item in sharedLog if item in logFile and sharedLog[item][0] == 'file_added']
    
    for item in files_updated:
        del sharedLog[item]

    files_added = []
    files_removed = []

    for item in sharedLog:
        if (sharedLog[item][0] == 'file_added'):
            files_added.append(item)
        elif (sharedLog[item][0] == 'file_removed'):
            files_removed.append(item)

    for item in files_removed:
        if item in logFile:
            del logFile[item]
        if item in clientFiles:
            del clientFiles[item]

    files_updated = []
    files_updated = [item for item in clientFiles if item in logFile and clientFiles[item] < os.stat(dir_path + client_id + '/' + item)[8]]

    if (files_added or files_updated):
        c_conn.send('f_add')
        files_list = files_added + files_updated
        pushFiles(c_conn, dir_path, client_id, files_list)
    else:
        c_conn.send('n_add')

    if (files_removed):
        c_conn.send('f_rem')
        sendRemoveFiles(c_conn, files_removed)
    else:
        c_conn.send('n_rem')   

    filesToAdd = {}
    filesToRem = {}
    filesToUpdate = {}
    dict([(item, os.stat(dir_path + client_id + '/' + item)[8]) for item in os.listdir(dir_path + client_id) if not item in files_private])

    filesToAdd = dict([(item, item ) for item in clientFiles if not item in logFile])
    filesToRem = dict([(item, item) for item in logFile if not item in clientFiles])
    filesToUpdate = dict([(item, item) for item in clientFiles if item in logFile and clientFiles[item] > os.stat(dir_path + client_id + '/' + item)[8]])

    filesToAddnUpdate = filesToAdd.copy()
    filesToAddnUpdate.update(filesToUpdate)

    sendList(c_conn, filesToAddnUpdate)
    sendList(c_conn, filesToRem)

    clientShare_list = {}
    sharedFiles_list = {}
    readShare(dir_path, client_id, 'ClientShare.dropbin', clientShare_list)
    readShare(dir_path, client_id, 'SharedFiles.dropbin', sharedFiles_list)

    op = c_conn.recv(5)
    if (op == 'f_add'):
        pullFiles(c_conn, dir_path, client_id, clientShare_list, sharedFiles_list)

    op = c_conn.recv(5)
    if (op == 'f_rem'):
        removeFiles(c_conn, dir_path, client_id, clientShare_list, sharedFiles_list)

def selectSync(c_conn, client_id, dir_path, syncList, files_private):
    syncMethod = c_conn.recv(5)
    c_conn.send('m_rec')
    if (syncMethod == 'nsync'):
        normalSync(c_conn, client_id, dir_path, files_private)
    elif (syncMethod == 'ssync'):
        selectiveSync(c_conn, client_id, dir_path, syncList, files_private)

def selectiveSync(c_conn, client_id, dir_path, syncList, files_private):
    dir_list = os.listdir(dir_path + client_id)
    new_dir_list = dict([(item, item) for item in dir_list if not item in files_private])
    sendList(c_conn, new_dir_list)
    recvList(c_conn, syncList)

    files_private = [item for item in dir_list if not item in syncList]

def clientHandler(c_conn, dir_path):
    while True:
        c_conn.send('Thank you for connecting')
        client_id = c_conn.recv(1024)    # Get client id from the user
        c_conn.send('c_rec')

        files_private = ['SharedFiles.dropbin', 'logfile.txt', 'sharedLog.txt']
        clientShare_before = {}
        sharedFiles_before = {}
        serverFiles_before = {}
        syncList = {}

        if not os.path.exists(dir_path + client_id):
            os.mkdir(dir_path + client_id)  # Makes the client's directory
            with open(dir_path + client_id + '/' + 'SharedFiles.dropbin', 'wb') as f:
                pass
            with open(dir_path + client_id + '/' + 'sharedLog.txt', 'wb') as f:
                pass
            c_conn.send('n_usr')
            pullFiles(c_conn, dir_path, client_id, clientShare_before, sharedFiles_before)
        else:
            c_conn.send('_sync')
            selectSync(c_conn, client_id, dir_path, syncList, files_private)

        while True:
            flag = 0

            clientShare_after = {}
            sharedFiles_after = {}

            readShare(dir_path, client_id, 'ClientShare.dropbin', clientShare_after)
            shareFiles(clientShare_before, clientShare_after, client_id)
                       
            op = c_conn.recv(5) # Recv op msg
            if (op == 'f_add'):
                pullFiles(c_conn, dir_path, client_id, clientShare_before, sharedFiles_before)
                flag = 1
            op = c_conn.recv(5)
            if (op == 'f_rem'):
                flag = 1
                removeFiles(c_conn, dir_path, client_id, clientShare_before, sharedFiles_before)
            
            if (syncList):
                files_private = []
                files_private = [item for item in os.listdir(dir_path + client_id) if not item in syncList]

            serverFiles_after = dict([(item, os.stat(dir_path + client_id + '/' + item)[8]) for item in os.listdir(dir_path + client_id) if not item in files_private])               

            if (flag == 0):
                pushChanges(serverFiles_after, serverFiles_before, c_conn, client_id, dir_path)

            readShare(dir_path, client_id, 'SharedFiles.dropbin', sharedFiles_after)

            sharedFiles_before = sharedFiles_after
            clientShare_before = clientShare_after
            serverFiles_before = serverFiles_after

            if (not syncList):
                with open(dir_path + client_id + '/' + 'sharedLog.txt', 'wb') as f:
                    pass

            updateLogFile(dir_path, client_id)

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
    