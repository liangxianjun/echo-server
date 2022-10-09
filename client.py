import socket
tcp_client_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM) 
tcp_client_socket.connect(('127.0.0.1', 14514))
while 1:
    send=input("send：")
    tcp_client_socket.send(send.encode("utf-8"))
tcp_client_socket.close()