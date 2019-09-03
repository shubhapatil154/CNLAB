from socket import *
serverName = 'bmsce-Precision-T1700'
serverPort = 15000
clientSocket = socket(AF_INET,SOCK_DGRAM)
sentence = input("ENTER FILE NAME\n")
clientSocket.sendto(bytes(sentence,"utf-8"),(serverName,serverPort))
filecontents,serverAddress = clientSocket.recvfrom(2048)
print("FROM SERVER ",filecontents.decode())
