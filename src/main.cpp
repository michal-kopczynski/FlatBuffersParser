#include <iostream>
#include <thread>
#include <vector>

#include "cxxopts.hpp"

#include "Socket.hpp"
#include "Parser.hpp"
#include "Client.hpp"


int main(int argc, char ** argv) {
    cxxopts::Options options("FlatBuffersParser", "FlatBuffers Parser is socket based tool for parsing binary FlatBuffers data to JSON format.");

    options.add_options()
        ("p,port", "Port to listen", cxxopts::value<int>())
        ("f,file", "Schema files", cxxopts::value<std::string>())
        ;

    auto result = options.parse(argc, argv);

    int port;
    std::string schemaFile;

    if (result.count("file")) {
        schemaFile = result["file"].as<std::string>();
    }
    else {
        std::cout << "Please specify schema file!" << std::endl;
        return -1;
    }

    if (result.count("port")) {
        port = result["port"].as<int>();
    }
    else {
        std::cout << "Please specify port!" << std::endl;
        return -1;
    }
    std::cout << result["f"].as<std::string>() << std::endl;
    std::cout << result["file"].as<std::string>() << std::endl;

    auto parser = std::make_shared<Parser>();

    std::cout << "Loading schema file: " << schemaFile << std::endl;
    parser->loadFile(schemaFile);

    Socket socket;
    socket.bind("127.0.0.1", port);
    socket.listen();

    std::cout << "FlatBuffers parser started." << std::endl;
    std::cout << "Listening on port: " << port << std::endl;

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