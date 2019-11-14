#include <iostream>
#include <thread>
#include <vector>

#include "Socket.hpp"
#include "Parser.hpp"
#include "Client.hpp"


int main(int argc, const char * argv []) {
//TODO: pass also port as a parameter
    static constexpr int port = 12345;
    std::cout << "FlatBuffers parser started." << std::endl;

    auto parser = std::make_shared<Parser>();

    for (int i = 1; i < argc; ++i) {
        std::cout << "Loading schema file: " << argv[i] << std::endl;
        parser->LoadFile(argv[i]);
    }

    Socket socket;
    socket.bind("127.0.0.1", port);
    std::cout << "Listening on port: " << port << std::endl;
    socket.listen();

    std::vector<std::unique_ptr<Client>> clients;
    for (;;)
    {
        std::cout << "Waiting for client " << clients.size() << std::endl;
        auto client = std::make_unique<Client>(socket.accept(), parser);
        std::cout << "Client " << clients.size() << " conected" << std::endl;
        clients.push_back(std::move(client));
    }

//    for ( auto &client : clients)
//    {
//        client.join();
//    }

    std::cout << "FlatBuffers parser finished!" << std::endl;
    return 1;
}