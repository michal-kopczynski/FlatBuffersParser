#include "WebSocketHandler.hpp"

#include <iostream>

#include "Parser.hpp"
#include "WebsocketReqMessage.hpp"
#include "WebsocketRespMessage.hpp"

WebSocketHandler::WebSocketHandler(Parser const& parser) :
parser(parser)
{
}

std::string const WebSocketHandler::handleMessage(std::string const& message) {
    WebsocketReqMessage reqMessage(message);
    
    auto parsedStringPtr = parser.parseBuffer(reqMessage.decodedData);

    WebsocketRespMessage respMessage(reqMessage.type, reqMessage.id, parsedStringPtr);
    return std::string(respMessage.getBuffer());
}