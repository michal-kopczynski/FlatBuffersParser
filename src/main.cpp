#include <iostream>
#include <iterator>
#include <algorithm>

#include <boost/asio/signal_set.hpp>
#include "server/listener.hpp"
#include "server/shared_state.hpp"

#include "Arguments.hpp"
#include "Parser.hpp"
#include "WebsocketHandler.hpp"

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

    auto parser = std::make_shared<Parser>();

    for (const auto& f : arguments.schemaFiles)
    {
        std::cout << "Loading schema file: " << f << std::endl;
        try {
            parser->loadFile(f);
        } catch (const char* msg) {
            std::cerr << msg << std::endl;
            return -1;
        }
    }

    auto address = net::ip::make_address("0.0.0.0");
    auto port = static_cast<unsigned short>(arguments.port);

    std::cout << "Starting  listener at address: " << address << " Port: " << port << std::endl;

    auto handler = std::make_shared<WebsocketHandler>(parser);

    // The io_context is required for all I/O
    net::io_context ioc;

    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        std::make_shared<shared_state>([&handler](const void* data) -> std::shared_ptr<std::string const>
        {
            return handler->handleMessage(data);
        }))->run();

    // Capture SIGINT and SIGTERM to perform a clean shutdown
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&ioc](boost::system::error_code const&, int)
        {
            // Stop the io_context. This will cause run()
            // to return immediately, eventually destroying the
            // io_context and any remaining handlers in it.
            ioc.stop();
        });

    // Run the I/O service on the main thread
    ioc.run();

    std::cout << "FlatBuffers parser finished!" << std::endl;
    return 1;
}