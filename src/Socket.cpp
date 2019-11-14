#include "Socket.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include "string.h"

Socket::Socket() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int socketFd) : socketFd(socketFd)
{
}

Socket::~Socket() {
    if (socketFd){
        ::close(socketFd);
    }
}
int Socket::bind(std::string ip, unsigned int port) {
    std::cout << "bind. ip: " << ip << ", port: " << port << std::endl;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    auto status = ::bind(socketFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    std::cout << "bind. status: " << status << std::endl;
    return status;
}
//1
int Socket::listen() { //int max connections param
    ::listen(socketFd,5);
    return socketFd;
}
std::unique_ptr<Socket> Socket::accept() {
    auto clientFd = ::accept(socketFd, (struct sockaddr*)NULL, NULL);
    if (clientFd != -1)
    {
        std::cout << "client accepted" << std::endl;
        return std::make_unique<Socket>(clientFd);
    }
    else
    {
        std::cout << "client accept failed" << std::endl;
        return 0;
    }

}
int Socket::connect(std::string ip, unsigned int port) {
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(::inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    serv_addr.sin_port = htons(port);
    if (::connect(socketFd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        std::cout << "ERROR connecting" << std::endl;

    return 1;
}
int Socket::send(const char* data, std::size_t size) {
    return ::send(socketFd , data, size , 0 );
}

int Socket::receive(char* data, std::size_t size) {
    return ::recv(socketFd, data, size, 0);
}