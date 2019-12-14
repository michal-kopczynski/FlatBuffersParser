#pragma once

#include <memory>

#include <restinio/all.hpp>
#include <restinio/websocket/websocket.hpp>

#include "HttpRouter.hpp"

namespace restinio_ws = restinio::websocket::basic;

using ws_registry_t = std::map< std::uint64_t, restinio_ws::ws_handle_t >;

class Server
{
public:
    Server( std::string addr,
            std::uint16_t port,
            std::unique_ptr<HttpRouter> httpRouter,
            std::function<std::string(std::string const&)> websocketHandler);
    ~Server();

    void run();

private:
    auto createServerHandler( ws_registry_t & registry );
    auto handleWebSocketUpgrade(
	    ws_registry_t & registry,
	    restinio::request_handle_t & req );
    void wsHandler(
	    ws_registry_t & registry,
	    restinio_ws::ws_handle_t wsh, 
	    restinio_ws::message_handle_t m );

    std::unique_ptr<HttpRouter> httpRouter;
    std::function<std::string(std::string const&)> websocketHandler;
    std::string addr;
    std::uint16_t port;
};
