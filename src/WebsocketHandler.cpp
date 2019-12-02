#include "WebsocketHandler.hpp"

#include <iostream>

#include "Parser.hpp"
#include "WebsocketReqMessage.hpp"
#include "WebsocketRespMessage.hpp"

WebsocketHandler::WebsocketHandler(std::shared_ptr<Parser> parser) :
parser(parser)
{
}

std::shared_ptr<std::string const> WebsocketHandler::handleMessage(std::shared_ptr<std::string const> const& ss) {
    return parser->parseBuffer(ss->data());
}

std::shared_ptr<std::string const> WebsocketHandler::handleMessage(const void * message) {
    WebsocketReqMessage reqMessage(message);
    
    auto parsedStringPtr = parser->parseBuffer(reqMessage.decodedData);

    WebsocketRespMessage respMessage(reqMessage.type, reqMessage.id, parsedStringPtr);

    return std::make_shared<std::string>(respMessage.getBuffer());
}