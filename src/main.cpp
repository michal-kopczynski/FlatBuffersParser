#include <iostream>
#include <thread>
#include <vector>

#include "Arguments.hpp"
#include "Socket.hpp"
#include "Parser.hpp"
#include "Client.hpp"


int main(int argc, char ** argv) {
    Arguments arguments;
    try {
        arguments.parse(argc, argv);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    auto parser = std::make_shared<Parser>();

    std::cout << "Loading schema file: " << arguments.schemaFile << std::endl;
    try {
        parser->loadFile(arguments.schemaFile);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    Socket socket;
    socket.bind("127.0.0.1", arguments.port);
    socket.listen();

    std::cout << "FlatBuffers parser started." << std::endl;
    std::cout << "Listening on port: " << arguments.port << std::endl;

    std::vector<std::unique_ptr<Client>> clients;
    for (;;)
    {
        std::cout << "Waiting for client " << clients.size() << std::endl;
        auto client = std::make_unique<Client>(socket.accept(), parser);
        std::cout << "Client " << clients.size() << " conected" << std::endl;
        clients.push_back(std::move(client));
    }

    std::cout << "FlatBuffers parser finished!" << std::endl;
    return 1;
}