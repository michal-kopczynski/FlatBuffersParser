#include "Client.hpp"

#include "Socket.hpp"
#include "Parser.hpp"

Client::Client(std::unique_ptr<Socket> socket, std::shared_ptr<Parser> parser) :
socket(std::move(socket)),
parser(parser),
thread(std::thread(&Client::serve, this))
{
}

void Client::serve() {
    std::cout << "Client thread started!" << std::endl;
    for (;;)
    {
        if (socket->receive(reqBuffer, 2000)){
            std::cout << "Request received" << std::endl;
            auto responseSize = parser->parseBuffer(reqBuffer, respBuffer);
            socket->send(respBuffer, responseSize);
            std::cout << "Response sent. Size: "<< responseSize << std::endl;
        }
    }
}