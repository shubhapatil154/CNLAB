from socket import *
serverName = 'bmsce-Precision-T1700'
serverPort = 12000from socket import *
serverName = 'bmsce-Precision-T1700'
serverPort = 12000
clientSocket = socket(AF_INET,SOCK_STREAM)
clientSocket.connect((serverName,serverPort))
sentence = input("ENTER THE FILE NAME")
clientSocket.send(sentence.encode())
filecontents = clientSocket.recv(1024).decode()
print("FROM SERVER",filecontents)
clientSocket.close()
