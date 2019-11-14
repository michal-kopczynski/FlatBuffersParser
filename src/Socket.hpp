#ifndef FLATBUFFERSPARSER_SOCKET_HPP
#define FLATBUFFERSPARSER_SOCKET_HPP

#include <string>

#include <iostream>
#include <memory>

class Socket {
public:
    Socket();
    Socket(int socketFd);
    ~Socket();
    int bind(std::string ip, unsigned int port);
    int listen(); //int max connections param
    std::unique_ptr<Socket> accept();
    int connect(std::string ip, unsigned int port);
    int send(const char* data, std::size_t size);
    int receive(char*, std::size_t size);
private:
    int socketFd = 0;
};


#endif //FLATBUFFERSPARSER_SOCKET_HPP
