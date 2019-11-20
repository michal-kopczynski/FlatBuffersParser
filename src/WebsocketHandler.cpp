#include "WebsocketHandler.hpp"

#include <iostream>

#include "Parser.hpp"

WebsocketHandler::WebsocketHandler(std::shared_ptr<Parser> parser) :
parser(parser)
{
}

std::shared_ptr<std::string const> WebsocketHandler::handleMessage(std::shared_ptr<std::string const> const& ss) {
    return parser->parseBuffer(ss->data());
}

std::shared_ptr<std::string const> WebsocketHandler::handleMessage(const void * data) {
    return parser->parseBuffer(data);
}