from socket import *
serverName = 'bmsce-Precision-T1700'
serverPort = 15000
serverSocket = socket(AF_INET,SOCK_DGRAM)
serverSocket.bind((serverName,serverPort))
print("THE SERVER IS READY TO RECIEVE\n")
while 1:
    sentence,clientAddress = serverSocket.recvfrom(2048)
    file = open(sentence,"r")
    line = file.read(1024)
    serverSocket.sendto((line.encode()),clientAddress)
    file.close()
