#include "Server.hpp"

#include <iostream>
#include <functional>

using server_traits_t = restinio::default_single_thread_traits_t;

Server::Server(std::string addr,
				std::uint16_t port,
				std::unique_ptr<HttpRouter> httpRouter,
				std::function<std::string(std::string const&)> websocketHandler) : 
addr(addr), 
port(port),
httpRouter(std::move(httpRouter)),
websocketHandler(websocketHandler)
{
}

Server::~Server() = default;

void Server::wsHandler(
	ws_registry_t & registry,
	restinio_ws::ws_handle_t wsh, 
	restinio_ws::message_handle_t m )
{
	if( m->opcode() == restinio_ws::opcode_t::connection_close_frame )
	{
		registry.erase( wsh->connection_id() );

		wsh->shutdown();
	}
	else
	{
		m->set_payload(websocketHandler(m->payload()));
		wsh->send_message( *m );
	}
};

auto Server::handleWebSocketUpgrade(
	ws_registry_t & registry,
	restinio::request_handle_t & req )
{
	using namespace std::placeholders;

	auto wsh = restinio_ws::upgrade<server_traits_t>(
			*req,
			restinio_ws::activation_t::immediate,
			std::bind( &Server::wsHandler, this, std::ref(registry), _1, _2 ) );

	registry.emplace( wsh->connection_id(), wsh );

	return restinio::request_accepted();
}

auto Server::createServerHandler( ws_registry_t & registry )
{
	return [&registry, this](auto req)
		{
			try
			{
				if( restinio::http_connection_header_t::upgrade
						== req->header().connection() )
					return handleWebSocketUpgrade( registry, req );
				else
					return httpRouter->handle( req );
			}
			catch( const std::exception & x )
			{
				std::cerr << "Exception caught: " << x.what() << std::endl;
				return restinio::request_rejected();
			}
		};
}

void Server::run()
{
    ws_registry_t registry;
    std::cout << "Server::run" << std::endl;

	restinio::run(
		restinio::on_this_thread<server_traits_t>()
			.address( addr )
			.port( port )
			.request_handler( createServerHandler( registry ) )
			.cleanup_func( [&]{ registry.clear(); } ) );		
}
