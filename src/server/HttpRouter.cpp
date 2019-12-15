#include "HttpRouter.hpp"

void HttpRouter::addHandler(const std::string path, handler_t handler)
{
    if (handlers.find(path) == handlers.end())
    {
        handlers[path] = handler;
    }
    else
    {
        std::cout << "Hendler " << path << " already registered!" << std::endl;
        throw PathAlreadyAddedException();
    }
}

restinio::request_handling_status_t HttpRouter::handle(restinio::request_handle_t & req)
{
    const auto & target = req->header().path();

    if (handlers.find(std::string(target)) != handlers.end())
    {
        auto [respBody, contentType] = handlers[std::string(target)](req->body());
        return req->create_response()
            .append_header( restinio::http_field::server, "FlatBuffersParser" )
            .append_header_date_field()
            .append_header( restinio::http_field::content_type, contentType)
            .set_body( std::move(respBody) )
            .done();
    }
    else
    {
        std::cout << "HttpRouter::handle: Handler not found for target: " << target << std::endl; 
        return req->create_response( restinio::status_bad_request() )
			.append_header_date_field()
			.connection_close()
			.done();
    }
}