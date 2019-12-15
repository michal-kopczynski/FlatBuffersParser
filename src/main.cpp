#include <iostream>
#include <iterator>
#include <algorithm>

#include <functional>

#include "Arguments.hpp"
#include "Parser.hpp"
#include "HttpHandler.hpp"
#include "WebSocketHandler.hpp"
#include "server/HttpRouter.hpp"
#include "server/Server.hpp"

int main(int argc, char ** argv) {
    Arguments arguments;
    try {
        arguments.parse(argc, argv);
    } catch (SchemaFileNotSpecifiedException& e) {
        std::cerr << "Schema file not specified!" << std::endl;
        return -1;
    } catch (PortNotSpecifiedException& e) {
        std::cerr << "Port not specified!" << std::endl;
        return -1;
    }

    Parser parser;
    for (const auto& f : arguments.schemaFiles)
    {
        std::cout << "Loading schema file: " << f << std::endl;
        try {
            parser.loadFile(f);
        } catch (const char* msg) {
            std::cerr << msg << std::endl;
            return -1;
        }
    }

    HttpHandler httpHandler(parser);
    WebSocketHandler webSocketHandler(parser);

    auto httpRouter = std::make_unique<HttpRouter>();
    try {
        httpRouter->addHandler(std::string("/bin_to_json"), [&httpHandler](auto reqBuffer) { 
            return httpHandler.handleBinToJsonRequest(reqBuffer);
        } );
    } catch (PathAlreadyAddedException& e) {
        return -1;
    }

    Server server(  "localhost", 
                    arguments.port, 
                    std::move(httpRouter), 
                    [&webSocketHandler](std::string const& m){
                        return webSocketHandler.handleMessage(m);
                    });
    server.run();
    
    std::cout << "FlatBuffers parser finished!" << std::endl;
    return 1;
}