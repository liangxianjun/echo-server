#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include <iostream>
#include <cstring>
#include <string>
#include <thread> 
#include <mutex>
#include <iomanip>

#include "logger.h"

static logger l;

void serve(int client_socket) {
    l.log(0, "client:"+std::to_string(client_socket), "serving");
    char buffer[1024];
    while(1) {
        memset(buffer, 0, sizeof(buffer));
        if(recv(client_socket, buffer, sizeof(buffer), 0)<=0) {
            break;
        } 

        l.log(0, "from client:"+std::to_string(client_socket), "received:"+std::string(buffer));
        write(client_socket, buffer, sizeof(buffer));
        l.log(0, "to client:"+std::to_string(client_socket), "wrote:"+std::string(buffer));
    }
    close(client_socket);
    l.log(0, "client:"+std::to_string(client_socket), "closed");
}

static volatile bool serving = true;

#define PORT 14514
int main() {
    l.log(0, "server\t", "start");

    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, SOMAXCONN);
    l.log(0, "server\t", "listening port:"+std::to_string(PORT));

    struct sockaddr_in client_address;
    socklen_t socklen = sizeof(struct sockaddr_in);
    int client_socket;

    while(serving) {
        client_socket = accept(server_socket,(struct sockaddr *)&client_address,(socklen_t*)&socklen);
        l.log(0, "client:"+std::to_string(client_socket), "accepted");
        std::thread(serve, client_socket).detach();
    }

    close(server_socket);
    l.log(0, "server\t", "closed");
    return 0;
}