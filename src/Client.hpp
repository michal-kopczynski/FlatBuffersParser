#ifndef FLATBUFFERSPARSER_CLIENT_HPP
#define FLATBUFFERSPARSER_CLIENT_HPP

#include <memory>
#include <thread>

class Socket;
class Parser;

class Client {
public:
    Client(std::unique_ptr<Socket> socket, std::shared_ptr<Parser> parser);
private:
    void serve();

    std::unique_ptr<Socket> socket;
    std::shared_ptr<Parser> parser;
    std::thread thread;
    char reqBuffer[2000];
    char respBuffer[20000];
};


#endif //FLATBUFFERSPARSER_CLIENT_HPP