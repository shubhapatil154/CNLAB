from socket import *
serverName = 'bmsce-Precision-T1700'
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind((serverName,serverPort))
serverSocket.listen(1)
print('THE SERVER IS READY TO RECIEVE')
while 1:
    connectionSocket,addr = serverSocket.accept()
    sentence = connectionSocket.recv(1024).decode()
    file = open(sentence,"r")
    line = file.read(1024)
    connectionSocket.send(line.encode())
    file.close()
    connectionSocket.close()
